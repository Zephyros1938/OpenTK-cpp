/*
Copyright (c) 2006 - 2008 The Open Toolkit library.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

using System;
using System.Diagnostics.Contracts;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Xml.Serialization;

namespace OpenTK.Mathematics
{
    [Serializable, StructLayout(LayoutKind.Sequential)]
    public struct Quaternion : IEquatable<Quaternion>, IFormattable
    {
        public Vector3 Xyz;

        public float W;

        public Quaternion(Vector3 v, float w)
        {
            Xyz = v;
            W = w;
        }

        public Quaternion(float x, float y, float z, float w)
            : this(new Vector3(x, y, z), w)
        {
        }

        public Quaternion(float rotationX, float rotationY, float rotationZ)
        {
            rotationX *= 0.5f;
            rotationY *= 0.5f;
            rotationZ *= 0.5f;

            var c1 = MathF.Cos(rotationX);
            var c2 = MathF.Cos(rotationY);
            var c3 = MathF.Cos(rotationZ);
            var s1 = MathF.Sin(rotationX);
            var s2 = MathF.Sin(rotationY);
            var s3 = MathF.Sin(rotationZ);

            W = (c1 * c2 * c3) - (s1 * s2 * s3);
            Xyz.X = (s1 * c2 * c3) + (c1 * s2 * s3);
            Xyz.Y = (c1 * s2 * c3) - (s1 * c2 * s3);
            Xyz.Z = (c1 * c2 * s3) + (s1 * s2 * c3);
        }

        public Quaternion(Vector3 eulerAngles)
            : this(eulerAngles.X, eulerAngles.Y, eulerAngles.Z)
        {
        }

        [XmlIgnore]
        public float X
        {
            readonly get => Xyz.X;
            set => Xyz.X = value;
        }

        [XmlIgnore]
        public float Y
        {
            readonly get => Xyz.Y;
            set => Xyz.Y = value;
        }

        [XmlIgnore]
        public float Z
        {
            readonly get => Xyz.Z;
            set => Xyz.Z = value;
        }

        public void ToAxisAngle(out Vector3 axis, out float angle)
        {
            var result = ToAxisAngle();
            axis = result.Xyz;
            angle = result.W;
        }

        public Vector4 ToAxisAngle()
        {
            var q = this;
            if (Math.Abs(q.W) > 1.0f)
            {
                q.Normalize();
            }

            var result = new Vector4
            {
                W = 2.0f * MathF.Acos(q.W) // angle
            };

            var den = MathF.Sqrt(1.0f - (q.W * q.W));
            if (den > 0.0001f)
            {
                result.Xyz = q.Xyz / den;
            }
            else
            {
                result.Xyz = Vector3.UnitX;
            }

            return result;
        }

        public readonly void ToEulerAngles(out Vector3 angles)
        {
            angles = ToEulerAngles();
        }

        public readonly Vector3 ToEulerAngles()
        {
            /*
            reference
            http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
            http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
            */

            var q = this;

            Vector3 eulerAngles;

            const float SINGULARITY_THRESHOLD = 0.4999995f;

            var sqw = q.W * q.W;
            var sqx = q.X * q.X;
            var sqy = q.Y * q.Y;
            var sqz = q.Z * q.Z;
            var unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
            var singularityTest = (q.X * q.Z) + (q.W * q.Y);

            if (singularityTest > SINGULARITY_THRESHOLD * unit)
            {
                eulerAngles.Z = 2 * MathF.Atan2(q.X, q.W);
                eulerAngles.Y = MathHelper.PiOver2;
                eulerAngles.X = 0;
            }
            else if (singularityTest < -SINGULARITY_THRESHOLD * unit)
            {
                eulerAngles.Z = -2 * MathF.Atan2(q.X, q.W);
                eulerAngles.Y = -MathHelper.PiOver2;
                eulerAngles.X = 0;
            }
            else
            {
                eulerAngles.Z = MathF.Atan2(2 * ((q.W * q.Z) - (q.X * q.Y)), sqw + sqx - sqy - sqz);
                eulerAngles.Y = MathF.Asin(2 * singularityTest / unit);
                eulerAngles.X = MathF.Atan2(2 * ((q.W * q.X) - (q.Y * q.Z)), sqw - sqx - sqy + sqz);
            }

            return eulerAngles;
        }

        public readonly float Length => MathF.Sqrt((W * W) + Xyz.LengthSquared);

        public readonly float LengthSquared => (W * W) + Xyz.LengthSquared;

        public readonly Quaternion Normalized()
        {
            var q = this;
            q.Normalize();
            return q;
        }

        public void Invert()
        {
            Invert(in this, out this);
        }

        public readonly Quaternion Inverted()
        {
            var q = this;
            q.Invert();
            return q;
        }

        public void Normalize()
        {
            var scale = 1.0f / Length;
            Xyz *= scale;
            W *= scale;
        }

        public void Conjugate()
        {
            Xyz = -Xyz;
        }

        public static readonly Quaternion Identity = new Quaternion(0, 0, 0, 1);

        [Pure]
        public static Quaternion Add(Quaternion left, Quaternion right)
        {
            return new Quaternion(
                left.Xyz + right.Xyz,
                left.W + right.W);
        }

        public static void Add(in Quaternion left, in Quaternion right, out Quaternion result)
        {
            result = new Quaternion(
                left.Xyz + right.Xyz,
                left.W + right.W);
        }

        [Pure]
        public static Quaternion Sub(Quaternion left, Quaternion right)
        {
            return new Quaternion(
                left.Xyz - right.Xyz,
                left.W - right.W);
        }

        public static void Sub(in Quaternion left, in Quaternion right, out Quaternion result)
        {
            result = new Quaternion(
                left.Xyz - right.Xyz,
                left.W - right.W);
        }

        [Pure]
        public static Quaternion Multiply(Quaternion left, Quaternion right)
        {
            Multiply(in left, in right, out Quaternion result);
            return result;
        }

        public static void Multiply(in Quaternion left, in Quaternion right, out Quaternion result)
        {
            result = new Quaternion(
                (right.W * left.Xyz) + (left.W * right.Xyz) + Vector3.Cross(left.Xyz, right.Xyz),
                (left.W * right.W) - Vector3.Dot(left.Xyz, right.Xyz));
        }

        public static void Multiply(in Quaternion quaternion, float scale, out Quaternion result)
        {
            result = new Quaternion
            (
                quaternion.X * scale,
                quaternion.Y * scale,
                quaternion.Z * scale,
                quaternion.W * scale
            );
        }

        [Pure]
        public static Quaternion Multiply(Quaternion quaternion, float scale)
        {
            return new Quaternion
            (
                quaternion.X * scale,
                quaternion.Y * scale,
                quaternion.Z * scale,
                quaternion.W * scale
            );
        }

        [Pure]
        public static Quaternion Conjugate(Quaternion q)
        {
            return new Quaternion(-q.Xyz, q.W);
        }

        public static void Conjugate(in Quaternion q, out Quaternion result)
        {
            result = new Quaternion(-q.Xyz, q.W);
        }

        [Pure]
        public static Quaternion Invert(Quaternion q)
        {
            Invert(in q, out Quaternion result);
            return result;
        }

        public static void Invert(in Quaternion q, out Quaternion result)
        {
            var lengthSq = q.LengthSquared;
            if (lengthSq != 0.0)
            {
                var i = 1.0f / lengthSq;
                result = new Quaternion(q.Xyz * -i, q.W * i);
            }
            else
            {
                result = q;
            }
        }

        [Pure]
        public static Quaternion Normalize(Quaternion q)
        {
            Normalize(in q, out Quaternion result);
            return result;
        }

        public static void Normalize(in Quaternion q, out Quaternion result)
        {
            var scale = 1.0f / q.Length;
            result = new Quaternion(q.Xyz * scale, q.W * scale);
        }

        [Pure]
        public static Quaternion FromAxisAngle(Vector3 axis, float angle)
        {
            if (axis.LengthSquared == 0.0f)
            {
                return Identity;
            }

            var result = Identity;

            angle *= 0.5f;
            axis.Normalize();
            result.Xyz = axis * MathF.Sin(angle);
            result.W = MathF.Cos(angle);

            return Normalize(result);
        }

        [Pure]
        public static Quaternion FromEulerAngles(float pitch, float yaw, float roll)
        {
            return new Quaternion(pitch, yaw, roll);
        }

        [Pure]
        public static Quaternion FromEulerAngles(Vector3 eulerAngles)
        {
            return new Quaternion(eulerAngles);
        }

        public static void FromEulerAngles(in Vector3 eulerAngles, out Quaternion result)
        {
            var c1 = MathF.Cos(eulerAngles.X * 0.5f);
            var c2 = MathF.Cos(eulerAngles.Y * 0.5f);
            var c3 = MathF.Cos(eulerAngles.Z * 0.5f);
            var s1 = MathF.Sin(eulerAngles.X * 0.5f);
            var s2 = MathF.Sin(eulerAngles.Y * 0.5f);
            var s3 = MathF.Sin(eulerAngles.Z * 0.5f);

            result.W = (c1 * c2 * c3) - (s1 * s2 * s3);
            result.Xyz.X = (s1 * c2 * c3) + (c1 * s2 * s3);
            result.Xyz.Y = (c1 * s2 * c3) - (s1 * c2 * s3);
            result.Xyz.Z = (c1 * c2 * s3) + (s1 * s2 * c3);
        }

        public static void ToEulerAngles(in Quaternion q, out Vector3 result)
        {
            q.ToEulerAngles(out result);
        }

        [Pure]
        public static Quaternion FromMatrix(Matrix3 matrix)
        {
            FromMatrix(in matrix, out Quaternion result);
            return result;
        }

        public static void FromMatrix(in Matrix3 matrix, out Quaternion result)
        {
            var trace = matrix.Trace;

            if (trace > 0)
            {
                var s = MathF.Sqrt(trace + 1) * 2;
                var invS = 1f / s;

                result.W = s * 0.25f;
                result.Xyz.X = (matrix.Row2.Y - matrix.Row1.Z) * invS;
                result.Xyz.Y = (matrix.Row0.Z - matrix.Row2.X) * invS;
                result.Xyz.Z = (matrix.Row1.X - matrix.Row0.Y) * invS;
            }
            else
            {
                float m00 = matrix.Row0.X, m11 = matrix.Row1.Y, m22 = matrix.Row2.Z;

                if (m00 > m11 && m00 > m22)
                {
                    var s = MathF.Sqrt(1 + m00 - m11 - m22) * 2;
                    var invS = 1f / s;

                    result.W = (matrix.Row2.Y - matrix.Row1.Z) * invS;
                    result.Xyz.X = s * 0.25f;
                    result.Xyz.Y = (matrix.Row0.Y + matrix.Row1.X) * invS;
                    result.Xyz.Z = (matrix.Row0.Z + matrix.Row2.X) * invS;
                }
                else if (m11 > m22)
                {
                    var s = MathF.Sqrt(1 + m11 - m00 - m22) * 2;
                    var invS = 1f / s;

                    result.W = (matrix.Row0.Z - matrix.Row2.X) * invS;
                    result.Xyz.X = (matrix.Row0.Y + matrix.Row1.X) * invS;
                    result.Xyz.Y = s * 0.25f;
                    result.Xyz.Z = (matrix.Row1.Z + matrix.Row2.Y) * invS;
                }
                else
                {
                    var s = MathF.Sqrt(1 + m22 - m00 - m11) * 2;
                    var invS = 1f / s;

                    result.W = (matrix.Row1.X - matrix.Row0.Y) * invS;
                    result.Xyz.X = (matrix.Row0.Z + matrix.Row2.X) * invS;
                    result.Xyz.Y = (matrix.Row1.Z + matrix.Row2.Y) * invS;
                    result.Xyz.Z = s * 0.25f;
                }
            }
        }

        [Pure]
        public static Quaternion Slerp(Quaternion q1, Quaternion q2, float blend)
        {
            if (q1.LengthSquared == 0.0f)
            {
                if (q2.LengthSquared == 0.0f)
                {
                    return Identity;
                }

                return q2;
            }

            if (q2.LengthSquared == 0.0f)
            {
                return q1;
            }

            var cosHalfAngle = (q1.W * q2.W) + Vector3.Dot(q1.Xyz, q2.Xyz);

            if (cosHalfAngle >= 1.0f || cosHalfAngle <= -1.0f)
            {
                return q1;
            }

            if (cosHalfAngle < 0.0f)
            {
                q2.Xyz = -q2.Xyz;
                q2.W = -q2.W;
                cosHalfAngle = -cosHalfAngle;
            }

            float blendA;
            float blendB;
            if (cosHalfAngle < 0.99f)
            {
                var halfAngle = MathF.Acos(cosHalfAngle);
                var sinHalfAngle = MathF.Sin(halfAngle);
                var oneOverSinHalfAngle = 1.0f / sinHalfAngle;
                blendA = MathF.Sin(halfAngle * (1.0f - blend)) * oneOverSinHalfAngle;
                blendB = MathF.Sin(halfAngle * blend) * oneOverSinHalfAngle;
            }
            else
            {
                blendA = 1.0f - blend;
                blendB = blend;
            }

            var result = new Quaternion((blendA * q1.Xyz) + (blendB * q2.Xyz), (blendA * q1.W) + (blendB * q2.W));
            if (result.LengthSquared > 0.0f)
            {
                return Normalize(result);
            }

            return Identity;
        }

        [Pure]
        public static Quaternion operator +(Quaternion left, Quaternion right)
        {
            left.Xyz += right.Xyz;
            left.W += right.W;
            return left;
        }

        [Pure]
        public static Quaternion operator -(Quaternion left, Quaternion right)
        {
            left.Xyz -= right.Xyz;
            left.W -= right.W;
            return left;
        }

        [Pure]
        public static Quaternion operator *(Quaternion left, Quaternion right)
        {
            Multiply(in left, in right, out left);
            return left;
        }

        [Pure]
        public static Quaternion operator *(Quaternion quaternion, float scale)
        {
            Multiply(in quaternion, scale, out quaternion);
            return quaternion;
        }

        [Pure]
        public static Quaternion operator *(float scale, Quaternion quaternion)
        {
            return new Quaternion
            (
                quaternion.X * scale,
                quaternion.Y * scale,
                quaternion.Z * scale,
                quaternion.W * scale
            );
        }

        public static bool operator ==(Quaternion left, Quaternion right)
        {
            return left.Equals(right);
        }

        public static bool operator !=(Quaternion left, Quaternion right)
        {
            return !(left == right);
        }

        [Pure]
        public static explicit operator Quaternion(System.Numerics.Quaternion quat)
        {
            return Unsafe.As<System.Numerics.Quaternion, Quaternion>(ref quat);
        }

        [Pure]
        public static explicit operator System.Numerics.Quaternion(Quaternion quat)
        {
            return Unsafe.As<Quaternion, System.Numerics.Quaternion>(ref quat);
        }

        public override readonly bool Equals(object obj)
        {
            return obj is Quaternion && Equals((Quaternion)obj);
        }

        public readonly bool Equals(Quaternion other)
        {
            return Xyz.Equals(other.Xyz) &&
                   W == other.W;
        }

        public override readonly int GetHashCode()
        {
            return HashCode.Combine(Xyz, W);
        }

        public override readonly string ToString()
        {
            return ToString(null, null);
        }

        public readonly string ToString(string format)
        {
            return ToString(format, null);
        }

        public readonly string ToString(IFormatProvider formatProvider)
        {
            return ToString(null, formatProvider);
        }

        public readonly string ToString(string format, IFormatProvider formatProvider)
        {
            var ls = MathHelper.GetListSeparator(formatProvider);
            var xyz = Xyz.ToString(format, formatProvider);
            var w = W.ToString(format, formatProvider);
            return $"V: {xyz}{ls} W: {w}";
        }
    }
}
