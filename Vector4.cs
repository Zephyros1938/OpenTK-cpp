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
using System.Globalization;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Xml.Serialization;

namespace OpenTK.Mathematics
{
    [Serializable]
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector4 : IEquatable<Vector4>, IFormattable
    {
        public float X;

        public float Y;

        public float Z;

        public float W;

        public static readonly Vector4 UnitX = new Vector4(1, 0, 0, 0);

        public static readonly Vector4 UnitY = new Vector4(0, 1, 0, 0);

        public static readonly Vector4 UnitZ = new Vector4(0, 0, 1, 0);

        public static readonly Vector4 UnitW = new Vector4(0, 0, 0, 1);

        public static readonly Vector4 Zero = new Vector4(0, 0, 0, 0);

        public static readonly Vector4 One = new Vector4(1, 1, 1, 1);

        public static readonly Vector4 PositiveInfinity = new Vector4(float.PositiveInfinity, float.PositiveInfinity, float.PositiveInfinity, float.PositiveInfinity);

        public static readonly Vector4 NegativeInfinity = new Vector4(float.NegativeInfinity, float.NegativeInfinity, float.NegativeInfinity, float.NegativeInfinity);

        public static readonly int SizeInBytes = Unsafe.SizeOf<Vector4>();

        public Vector4(float value)
        {
            X = value;
            Y = value;
            Z = value;
            W = value;
        }

        public Vector4(float x, float y, float z, float w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        public Vector4(Vector2 v)
        {
            X = v.X;
            Y = v.Y;
            Z = 0.0f;
            W = 0.0f;
        }

        public Vector4(Vector3 v)
        {
            X = v.X;
            Y = v.Y;
            Z = v.Z;
            W = 0.0f;
        }

        public Vector4(Vector3 v, float w)
        {
            X = v.X;
            Y = v.Y;
            Z = v.Z;
            W = w;
        }

        public Vector4(Vector4 v)
        {
            X = v.X;
            Y = v.Y;
            Z = v.Z;
            W = v.W;
        }

        public float this[int index]
        {
            readonly get
            {
                if (((uint)index) < 4)
                {
                    return GetElementUnsafe(in this, index);
                }
                else
                {
                    MathHelper.ThrowOutOfRangeException("You tried to access this vector at index: " + index);
                    return default;
                }
            }

            set
            {
                if (((uint)index) < 4)
                {
                    GetElementUnsafe(in this, index) = value;
                }
                else
                {
                    MathHelper.ThrowOutOfRangeException("You tried to set this vector at index: " + index);
                }
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private readonly ref float GetElementUnsafe(in Vector4 v, int index)
        {
            ref float address = ref Unsafe.AsRef(in v.X);
            return ref Unsafe.Add(ref address, index);
        }

        public readonly float Length => MathF.Sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));

        public readonly float ReciprocalLengthFast => MathHelper.InverseSqrtFast((X * X) + (Y * Y) + (Z * Z) + (W * W));

        public readonly float LengthFast => 1.0f / MathHelper.InverseSqrtFast((X * X) + (Y * Y) + (Z * Z) + (W * W));

        public readonly float LengthSquared => (X * X) + (Y * Y) + (Z * Z) + (W * W);

        public readonly Vector4 Normalized()
        {
            Vector4 v = this;
            v.Normalize();
            return v;
        }

        public void Normalize()
        {
            float scale = 1.0f / Length;
            X *= scale;
            Y *= scale;
            Z *= scale;
            W *= scale;
        }

        public void NormalizeFast()
        {
            float scale = MathHelper.InverseSqrtFast((X * X) + (Y * Y) + (Z * Z) + (W * W));
            X *= scale;
            Y *= scale;
            Z *= scale;
            W *= scale;
        }

        public readonly Vector4 Abs()
        {
            Vector4 result = this;
            result.X = MathF.Abs(result.X);
            result.Y = MathF.Abs(result.Y);
            result.Z = MathF.Abs(result.Z);
            result.W = MathF.Abs(result.W);
            return result;
        }

        public readonly Vector4 Round()
        {
            return Round(this);
        }

        public readonly Vector4 Round(MidpointRounding rounding)
        {
            return Round(this, rounding);
        }

        public readonly Vector4 Ceiling()
        {
            return Ceiling(this);
        }

        public readonly Vector4 Floor()
        {
            return Floor(this);
        }

        public readonly Vector4 Truncate()
        {
            return Truncate(this);
        }

        [Pure]
        public static Vector4 Add(Vector4 a, Vector4 b)
        {
            Add(in a, in b, out a);
            return a;
        }

        public static void Add(in Vector4 a, in Vector4 b, out Vector4 result)
        {
            result.X = a.X + b.X;
            result.Y = a.Y + b.Y;
            result.Z = a.Z + b.Z;
            result.W = a.W + b.W;
        }

        [Pure]
        public static Vector4 Subtract(Vector4 a, Vector4 b)
        {
            Subtract(in a, in b, out a);
            return a;
        }

        public static void Subtract(in Vector4 a, in Vector4 b, out Vector4 result)
        {
            result.X = a.X - b.X;
            result.Y = a.Y - b.Y;
            result.Z = a.Z - b.Z;
            result.W = a.W - b.W;
        }

        [Pure]
        public static Vector4 Multiply(Vector4 vector, float scale)
        {
            Multiply(in vector, scale, out vector);
            return vector;
        }

        public static void Multiply(in Vector4 vector, float scale, out Vector4 result)
        {
            result.X = vector.X * scale;
            result.Y = vector.Y * scale;
            result.Z = vector.Z * scale;
            result.W = vector.W * scale;
        }

        [Pure]
        public static Vector4 Multiply(Vector4 vector, Vector4 scale)
        {
            Multiply(in vector, in scale, out vector);
            return vector;
        }

        public static void Multiply(in Vector4 vector, in Vector4 scale, out Vector4 result)
        {
            result.X = vector.X * scale.X;
            result.Y = vector.Y * scale.Y;
            result.Z = vector.Z * scale.Z;
            result.W = vector.W * scale.W;
        }

        [Pure]
        public static Vector4 Divide(Vector4 vector, float scale)
        {
            Divide(in vector, scale, out vector);
            return vector;
        }

        public static void Divide(in Vector4 vector, float scale, out Vector4 result)
        {
            result.X = vector.X / scale;
            result.Y = vector.Y / scale;
            result.Z = vector.Z / scale;
            result.W = vector.W / scale;
        }

        [Pure]
        public static Vector4 Divide(Vector4 vector, Vector4 scale)
        {
            Divide(in vector, in scale, out vector);
            return vector;
        }

        public static void Divide(in Vector4 vector, in Vector4 scale, out Vector4 result)
        {
            result.X = vector.X / scale.X;
            result.Y = vector.Y / scale.Y;
            result.Z = vector.Z / scale.Z;
            result.W = vector.W / scale.W;
        }

        [Pure]
        public static Vector4 ComponentMin(Vector4 a, Vector4 b)
        {
            a.X = a.X < b.X ? a.X : b.X;
            a.Y = a.Y < b.Y ? a.Y : b.Y;
            a.Z = a.Z < b.Z ? a.Z : b.Z;
            a.W = a.W < b.W ? a.W : b.W;
            return a;
        }

        public static void ComponentMin(in Vector4 a, in Vector4 b, out Vector4 result)
        {
            result.X = a.X < b.X ? a.X : b.X;
            result.Y = a.Y < b.Y ? a.Y : b.Y;
            result.Z = a.Z < b.Z ? a.Z : b.Z;
            result.W = a.W < b.W ? a.W : b.W;
        }

        [Pure]
        public static Vector4 ComponentMax(Vector4 a, Vector4 b)
        {
            a.X = a.X > b.X ? a.X : b.X;
            a.Y = a.Y > b.Y ? a.Y : b.Y;
            a.Z = a.Z > b.Z ? a.Z : b.Z;
            a.W = a.W > b.W ? a.W : b.W;
            return a;
        }

        public static void ComponentMax(in Vector4 a, in Vector4 b, out Vector4 result)
        {
            result.X = a.X > b.X ? a.X : b.X;
            result.Y = a.Y > b.Y ? a.Y : b.Y;
            result.Z = a.Z > b.Z ? a.Z : b.Z;
            result.W = a.W > b.W ? a.W : b.W;
        }

        [Pure]
        public static Vector4 MagnitudeMin(Vector4 left, Vector4 right)
        {
            return left.LengthSquared < right.LengthSquared ? left : right;
        }

        public static void MagnitudeMin(in Vector4 left, in Vector4 right, out Vector4 result)
        {
            result = left.LengthSquared < right.LengthSquared ? left : right;
        }

        [Pure]
        public static Vector4 MagnitudeMax(Vector4 left, Vector4 right)
        {
            return left.LengthSquared >= right.LengthSquared ? left : right;
        }

        public static void MagnitudeMax(in Vector4 left, in Vector4 right, out Vector4 result)
        {
            result = left.LengthSquared >= right.LengthSquared ? left : right;
        }

        [Pure]
        public static Vector4 Clamp(Vector4 vec, Vector4 min, Vector4 max)
        {
            vec.X = vec.X < min.X ? min.X : vec.X > max.X ? max.X : vec.X;
            vec.Y = vec.Y < min.Y ? min.Y : vec.Y > max.Y ? max.Y : vec.Y;
            vec.Z = vec.Z < min.Z ? min.Z : vec.Z > max.Z ? max.Z : vec.Z;
            vec.W = vec.W < min.W ? min.W : vec.W > max.W ? max.W : vec.W;
            return vec;
        }

        public static void Clamp(in Vector4 vec, in Vector4 min, in Vector4 max, out Vector4 result)
        {
            result.X = vec.X < min.X ? min.X : vec.X > max.X ? max.X : vec.X;
            result.Y = vec.Y < min.Y ? min.Y : vec.Y > max.Y ? max.Y : vec.Y;
            result.Z = vec.Z < min.Z ? min.Z : vec.Z > max.Z ? max.Z : vec.Z;
            result.W = vec.W < min.W ? min.W : vec.W > max.W ? max.W : vec.W;
        }

        public static Vector4 Abs(Vector4 vec)
        {
            vec.X = MathF.Abs(vec.X);
            vec.Y = MathF.Abs(vec.Y);
            vec.Z = MathF.Abs(vec.Z);
            vec.W = MathF.Abs(vec.W);
            return vec;
        }

        public static void Abs(in Vector4 vec, out Vector4 result)
        {
            result.X = MathF.Abs(vec.X);
            result.Y = MathF.Abs(vec.Y);
            result.Z = MathF.Abs(vec.Z);
            result.W = MathF.Abs(vec.W);
        }

        [Pure]
        public static Vector4 Round(Vector4 vec)
        {
            vec.X = MathF.Round(vec.X);
            vec.Y = MathF.Round(vec.Y);
            vec.Z = MathF.Round(vec.Z);
            vec.W = MathF.Round(vec.W);
            return vec;
        }

        public static void Round(in Vector4 vec, out Vector4 result)
        {
            result.X = MathF.Round(vec.X);
            result.Y = MathF.Round(vec.Y);
            result.Z = MathF.Round(vec.Z);
            result.W = MathF.Round(vec.W);
        }

        [Pure]
        public static Vector4 Round(Vector4 vec, MidpointRounding rounding)
        {
            vec.X = MathF.Round(vec.X, rounding);
            vec.Y = MathF.Round(vec.Y, rounding);
            vec.Z = MathF.Round(vec.Z, rounding);
            vec.W = MathF.Round(vec.W, rounding);
            return vec;
        }

        public static void Round(in Vector4 vec, MidpointRounding rounding, out Vector4 result)
        {
            result.X = MathF.Round(vec.X, rounding);
            result.Y = MathF.Round(vec.Y, rounding);
            result.Z = MathF.Round(vec.Z, rounding);
            result.W = MathF.Round(vec.W, rounding);
        }

        [Pure]
        public static Vector4 Ceiling(Vector4 vec)
        {
            vec.X = MathF.Ceiling(vec.X);
            vec.Y = MathF.Ceiling(vec.Y);
            vec.Z = MathF.Ceiling(vec.Z);
            vec.W = MathF.Ceiling(vec.W);
            return vec;
        }

        public static void Ceiling(in Vector4 vec, out Vector4 result)
        {
            result.X = MathF.Ceiling(vec.X);
            result.Y = MathF.Ceiling(vec.Y);
            result.Z = MathF.Ceiling(vec.Z);
            result.W = MathF.Ceiling(vec.W);
        }

        [Pure]
        public static Vector4 Floor(Vector4 vec)
        {
            vec.X = MathF.Floor(vec.X);
            vec.Y = MathF.Floor(vec.Y);
            vec.Z = MathF.Floor(vec.Z);
            vec.W = MathF.Floor(vec.W);
            return vec;
        }

        public static void Floor(in Vector4 vec, out Vector4 result)
        {
            result.X = MathF.Floor(vec.X);
            result.Y = MathF.Floor(vec.Y);
            result.Z = MathF.Floor(vec.Z);
            result.W = MathF.Floor(vec.W);
        }

        [Pure]
        public static Vector4 Truncate(Vector4 vec)
        {
            vec.X = MathF.Truncate(vec.X);
            vec.Y = MathF.Truncate(vec.Y);
            vec.Z = MathF.Truncate(vec.Z);
            vec.W = MathF.Truncate(vec.W);
            return vec;
        }

        public static void Truncate(in Vector4 vec, out Vector4 result)
        {
            result.X = MathF.Truncate(vec.X);
            result.Y = MathF.Truncate(vec.Y);
            result.Z = MathF.Truncate(vec.Z);
            result.W = MathF.Truncate(vec.W);
        }

        [Pure]
        public static float Distance(Vector4 vec1, Vector4 vec2)
        {
            Distance(in vec1, in vec2, out float result);
            return result;
        }

        public static void Distance(in Vector4 vec1, in Vector4 vec2, out float result)
        {
            result = MathF.Sqrt(((vec2.X - vec1.X) * (vec2.X - vec1.X)) + ((vec2.Y - vec1.Y) * (vec2.Y - vec1.Y)) + ((vec2.Z - vec1.Z) * (vec2.Z - vec1.Z)) + ((vec2.W - vec1.W) * (vec2.W - vec1.W)));
        }

        [Pure]
        public static float DistanceSquared(Vector4 vec1, Vector4 vec2)
        {
            DistanceSquared(in vec1, in vec2, out float result);
            return result;
        }

        public static void DistanceSquared(in Vector4 vec1, in Vector4 vec2, out float result)
        {
            result = ((vec2.X - vec1.X) * (vec2.X - vec1.X)) + ((vec2.Y - vec1.Y) * (vec2.Y - vec1.Y)) + ((vec2.Z - vec1.Z) * (vec2.Z - vec1.Z)) + ((vec2.W - vec1.W) * (vec2.W - vec1.W));
        }

        [Pure]
        public static Vector4 Normalize(Vector4 vec)
        {
            float scale = 1.0f / vec.Length;
            vec.X *= scale;
            vec.Y *= scale;
            vec.Z *= scale;
            vec.W *= scale;
            return vec;
        }

        public static void Normalize(in Vector4 vec, out Vector4 result)
        {
            float scale = 1.0f / vec.Length;
            result.X = vec.X * scale;
            result.Y = vec.Y * scale;
            result.Z = vec.Z * scale;
            result.W = vec.W * scale;
        }

        [Pure]
        public static Vector4 NormalizeFast(Vector4 vec)
        {
            float scale = MathHelper.InverseSqrtFast((vec.X * vec.X) + (vec.Y * vec.Y) + (vec.Z * vec.Z) + (vec.W * vec.W));
            vec.X *= scale;
            vec.Y *= scale;
            vec.Z *= scale;
            vec.W *= scale;
            return vec;
        }

        public static void NormalizeFast(in Vector4 vec, out Vector4 result)
        {
            float scale = MathHelper.InverseSqrtFast((vec.X * vec.X) + (vec.Y * vec.Y) + (vec.Z * vec.Z) + (vec.W * vec.W));
            result.X = vec.X * scale;
            result.Y = vec.Y * scale;
            result.Z = vec.Z * scale;
            result.W = vec.W * scale;
        }

        [Pure]
        public static float Dot(Vector4 left, Vector4 right)
        {
            return (left.X * right.X) + (left.Y * right.Y) + (left.Z * right.Z) + (left.W * right.W);
        }

        public static void Dot(in Vector4 left, in Vector4 right, out float result)
        {
            result = (left.X * right.X) + (left.Y * right.Y) + (left.Z * right.Z) + (left.W * right.W);
        }

        public static Vector4b LessThan(in Vector4 left, in Vector4 right)
        {
            return new Vector4b(left.X < right.X, left.Y < right.Y, left.Z < right.Z, left.W < right.W);
        }

        public static Vector4b LessThanOrEqual(in Vector4 left, in Vector4 right)
        {
            return new Vector4b(left.X <= right.X, left.Y <= right.Y, left.Z <= right.Z, left.W <= right.W);
        }

        public static Vector4b GreaterThan(in Vector4 left, in Vector4 right)
        {
            return new Vector4b(left.X > right.X, left.Y > right.Y, left.Z > right.Z, left.W > right.W);
        }

        public static Vector4b GreaterThanOrEqual(in Vector4 left, in Vector4 right)
        {
            return new Vector4b(left.X >= right.X, left.Y >= right.Y, left.Z >= right.Z, left.W >= right.W);
        }

        public static Vector4b ComponentEqual(in Vector4 left, in Vector4 right)
        {
            return new Vector4b(left.X == right.X, left.Y == right.Y, left.Z == right.Z, left.W == right.W);
        }

        public static Vector4b ComponentNotEqual(in Vector4 left, in Vector4 right)
        {
            return new Vector4b(left.X != right.X, left.Y != right.Y, left.Z != right.Z, left.W != right.W);
        }

        [Pure]
        public static Vector4 Lerp(Vector4 a, Vector4 b, float blend)
        {
            a.X = (blend * (b.X - a.X)) + a.X;
            a.Y = (blend * (b.Y - a.Y)) + a.Y;
            a.Z = (blend * (b.Z - a.Z)) + a.Z;
            a.W = (blend * (b.W - a.W)) + a.W;
            return a;
        }

        public static void Lerp(in Vector4 a, in Vector4 b, float blend, out Vector4 result)
        {
            result.X = (blend * (b.X - a.X)) + a.X;
            result.Y = (blend * (b.Y - a.Y)) + a.Y;
            result.Z = (blend * (b.Z - a.Z)) + a.Z;
            result.W = (blend * (b.W - a.W)) + a.W;
        }

        [Pure]
        public static Vector4 Lerp(Vector4 a, Vector4 b, Vector4 blend)
        {
            a.X = (blend.X * (b.X - a.X)) + a.X;
            a.Y = (blend.Y * (b.Y - a.Y)) + a.Y;
            a.Z = (blend.Z * (b.Z - a.Z)) + a.Z;
            a.W = (blend.W * (b.W - a.W)) + a.W;
            return a;
        }

        public static void Lerp(in Vector4 a, in Vector4 b, Vector4 blend, out Vector4 result)
        {
            result.X = (blend.X * (b.X - a.X)) + a.X;
            result.Y = (blend.Y * (b.Y - a.Y)) + a.Y;
            result.Z = (blend.Z * (b.Z - a.Z)) + a.Z;
            result.W = (blend.W * (b.W - a.W)) + a.W;
        }

        [Pure]
        public static Vector4 Slerp(Vector4 a, Vector4 b, float t)
        {
            float abLength = a.Length * b.Length;
            float cosTheta;
            if (abLength == 0 || Math.Abs(cosTheta = Dot(a, b) / abLength) > 0.9999f)
            {
                return Lerp(a, b, t);
            }
            else
            {
                float theta = MathF.Acos(Math.Clamp(cosTheta, -1, 1));
                float sinTheta = MathF.Sqrt(1 - (cosTheta * cosTheta));
                float acoef = MathF.Sin((1 - t) * theta) / sinTheta;
                float bcoef = MathF.Sin(t * theta) / sinTheta;
                return (acoef * a) + (bcoef * b);
            }
        }

        public static void Slerp(in Vector4 a, in Vector4 b, float t, out Vector4 result)
        {
            float abLength = a.Length * b.Length;
            if (abLength == 0)
            {
                Lerp(in a, in b, t, out result);
            }
            else
            {
                Dot(in a, in b, out float cosTheta);
                cosTheta /= abLength;
                if (Math.Abs(cosTheta) > 0.9999f)
                {
                    Lerp(in a, in b, t, out result);
                }
                else
                {
                    float theta = MathF.Acos(cosTheta);
                    float sinTheta = MathF.Sqrt(1 - (cosTheta * cosTheta));
                    float acoef = MathF.Sin((1 - t) * theta) / sinTheta;
                    float bcoef = MathF.Sin(t * theta) / sinTheta;
                    result = (acoef * a) + (bcoef * b);
                }
            }
        }

        public static Vector4 Elerp(Vector4 a, Vector4 b, float t)
        {
            a.X = MathF.Pow(a.X, 1 - t) * MathF.Pow(b.X, t);
            a.Y = MathF.Pow(a.Y, 1 - t) * MathF.Pow(b.Y, t);
            a.Z = MathF.Pow(a.Z, 1 - t) * MathF.Pow(b.Z, t);
            a.W = MathF.Pow(a.W, 1 - t) * MathF.Pow(b.W, t);
            return a;
        }

        public static void Elerp(in Vector4 a, in Vector4 b, float t, out Vector4 result)
        {
            result.X = MathF.Pow(a.X, 1 - t) * MathF.Pow(b.X, t);
            result.Y = MathF.Pow(a.Y, 1 - t) * MathF.Pow(b.Y, t);
            result.Z = MathF.Pow(a.Z, 1 - t) * MathF.Pow(b.Z, t);
            result.W = MathF.Pow(a.W, 1 - t) * MathF.Pow(b.W, t);
        }

        [Pure]
        public static Vector4 BaryCentric(Vector4 a, Vector4 b, Vector4 c, float u, float v)
        {
            BaryCentric(in a, in b, in c, u, v, out Vector4 result);
            return result;
        }

        public static void BaryCentric
        (
            in Vector4 a,
            in Vector4 b,
            in Vector4 c,
            float u,
            float v,
            out Vector4 result
        )
        {
            Subtract(in b, in a, out Vector4 ab);
            Multiply(in ab, u, out Vector4 abU);
            Add(in a, in abU, out Vector4 uPos);

            Subtract(in c, in a, out Vector4 ac);
            Multiply(in ac, v, out Vector4 acV);
            Add(in uPos, in acV, out result);
        }

        [Pure]
        public static Vector4 TransformRow(Vector4 vec, Matrix4 mat)
        {
            TransformRow(in vec, in mat, out Vector4 result);
            return result;
        }

        public static void TransformRow(in Vector4 vec, in Matrix4 mat, out Vector4 result)
        {
            result = new Vector4(
                (vec.X * mat.Row0.X) + (vec.Y * mat.Row1.X) + (vec.Z * mat.Row2.X) + (vec.W * mat.Row3.X),
                (vec.X * mat.Row0.Y) + (vec.Y * mat.Row1.Y) + (vec.Z * mat.Row2.Y) + (vec.W * mat.Row3.Y),
                (vec.X * mat.Row0.Z) + (vec.Y * mat.Row1.Z) + (vec.Z * mat.Row2.Z) + (vec.W * mat.Row3.Z),
                (vec.X * mat.Row0.W) + (vec.Y * mat.Row1.W) + (vec.Z * mat.Row2.W) + (vec.W * mat.Row3.W));
        }

        [Pure]
        public static Vector4 Transform(Vector4 vec, Quaternion quat)
        {
            Transform(in vec, in quat, out Vector4 result);
            return result;
        }

        public static void Transform(in Vector4 vec, in Quaternion quat, out Vector4 result)
        {
            Quaternion v = new Quaternion(vec.X, vec.Y, vec.Z, vec.W);
            Quaternion.Invert(in quat, out Quaternion i);
            Quaternion.Multiply(in quat, in v, out Quaternion t);
            Quaternion.Multiply(in t, in i, out v);

            result.X = v.X;
            result.Y = v.Y;
            result.Z = v.Z;
            result.W = v.W;
        }

        [Pure]
        public static Vector4 TransformColumn(Matrix4 mat, Vector4 vec)
        {
            TransformColumn(in mat, in vec, out Vector4 result);
            return result;
        }

        public static void TransformColumn(in Matrix4 mat, in Vector4 vec, out Vector4 result)
        {
            result = new Vector4(
                (mat.Row0.X * vec.X) + (mat.Row0.Y * vec.Y) + (mat.Row0.Z * vec.Z) + (mat.Row0.W * vec.W),
                (mat.Row1.X * vec.X) + (mat.Row1.Y * vec.Y) + (mat.Row1.Z * vec.Z) + (mat.Row1.W * vec.W),
                (mat.Row2.X * vec.X) + (mat.Row2.Y * vec.Y) + (mat.Row2.Z * vec.Z) + (mat.Row2.W * vec.W),
                (mat.Row3.X * vec.X) + (mat.Row3.Y * vec.Y) + (mat.Row3.Z * vec.Z) + (mat.Row3.W * vec.W));
        }

        [XmlIgnore]
        public Vector2 Xy
        {
            get => Unsafe.As<Vector4, Vector2>(ref this);
            set
            {
                X = value.X;
                Y = value.Y;
            }
        }

        [XmlIgnore]
        public Vector2 Xz
        {
            readonly get => new Vector2(X, Z);
            set
            {
                X = value.X;
                Z = value.Y;
            }
        }

        [XmlIgnore]
        public Vector2 Xw
        {
            readonly get => new Vector2(X, W);
            set
            {
                X = value.X;
                W = value.Y;
            }
        }

        [XmlIgnore]
        public Vector2 Yx
        {
            readonly get => new Vector2(Y, X);
            set
            {
                Y = value.X;
                X = value.Y;
            }
        }

        [XmlIgnore]
        public Vector2 Yz
        {
            readonly get => new Vector2(Y, Z);
            set
            {
                Y = value.X;
                Z = value.Y;
            }
        }

        [XmlIgnore]
        public Vector2 Yw
        {
            readonly get => new Vector2(Y, W);
            set
            {
                Y = value.X;
                W = value.Y;
            }
        }

        [XmlIgnore]
        public Vector2 Zx
        {
            readonly get => new Vector2(Z, X);
            set
            {
                Z = value.X;
                X = value.Y;
            }
        }

        [XmlIgnore]
        public Vector2 Zy
        {
            readonly get => new Vector2(Z, Y);
            set
            {
                Z = value.X;
                Y = value.Y;
            }
        }

        [XmlIgnore]
        public Vector2 Zw
        {
            readonly get => new Vector2(Z, W);
            set
            {
                Z = value.X;
                W = value.Y;
            }
        }

        [XmlIgnore]
        public Vector2 Wx
        {
            readonly get => new Vector2(W, X);
            set
            {
                W = value.X;
                X = value.Y;
            }
        }

        [XmlIgnore]
        public Vector2 Wy
        {
            readonly get => new Vector2(W, Y);
            set
            {
                W = value.X;
                Y = value.Y;
            }
        }

        [XmlIgnore]
        public Vector2 Wz
        {
            readonly get => new Vector2(W, Z);
            set
            {
                W = value.X;
                Z = value.Y;
            }
        }

        [XmlIgnore]
        public Vector3 Xyz
        {
            get => Unsafe.As<Vector4, Vector3>(ref this);
            set
            {
                X = value.X;
                Y = value.Y;
                Z = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Xyw
        {
            readonly get => new Vector3(X, Y, W);
            set
            {
                X = value.X;
                Y = value.Y;
                W = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Xzy
        {
            readonly get => new Vector3(X, Z, Y);
            set
            {
                X = value.X;
                Z = value.Y;
                Y = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Xzw
        {
            readonly get => new Vector3(X, Z, W);
            set
            {
                X = value.X;
                Z = value.Y;
                W = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Xwy
        {
            readonly get => new Vector3(X, W, Y);
            set
            {
                X = value.X;
                W = value.Y;
                Y = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Xwz
        {
            readonly get => new Vector3(X, W, Z);
            set
            {
                X = value.X;
                W = value.Y;
                Z = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Yxz
        {
            readonly get => new Vector3(Y, X, Z);
            set
            {
                Y = value.X;
                X = value.Y;
                Z = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Yxw
        {
            readonly get => new Vector3(Y, X, W);
            set
            {
                Y = value.X;
                X = value.Y;
                W = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Yzx
        {
            readonly get => new Vector3(Y, Z, X);
            set
            {
                Y = value.X;
                Z = value.Y;
                X = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Yzw
        {
            readonly get => new Vector3(Y, Z, W);
            set
            {
                Y = value.X;
                Z = value.Y;
                W = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Ywx
        {
            readonly get => new Vector3(Y, W, X);
            set
            {
                Y = value.X;
                W = value.Y;
                X = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Ywz
        {
            readonly get => new Vector3(Y, W, Z);
            set
            {
                Y = value.X;
                W = value.Y;
                Z = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Zxy
        {
            readonly get => new Vector3(Z, X, Y);
            set
            {
                Z = value.X;
                X = value.Y;
                Y = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Zxw
        {
            readonly get => new Vector3(Z, X, W);
            set
            {
                Z = value.X;
                X = value.Y;
                W = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Zyx
        {
            readonly get => new Vector3(Z, Y, X);
            set
            {
                Z = value.X;
                Y = value.Y;
                X = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Zyw
        {
            readonly get => new Vector3(Z, Y, W);
            set
            {
                Z = value.X;
                Y = value.Y;
                W = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Zwx
        {
            readonly get => new Vector3(Z, W, X);
            set
            {
                Z = value.X;
                W = value.Y;
                X = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Zwy
        {
            readonly get => new Vector3(Z, W, Y);
            set
            {
                Z = value.X;
                W = value.Y;
                Y = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Wxy
        {
            readonly get => new Vector3(W, X, Y);
            set
            {
                W = value.X;
                X = value.Y;
                Y = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Wxz
        {
            readonly get => new Vector3(W, X, Z);
            set
            {
                W = value.X;
                X = value.Y;
                Z = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Wyx
        {
            readonly get => new Vector3(W, Y, X);
            set
            {
                W = value.X;
                Y = value.Y;
                X = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Wyz
        {
            readonly get => new Vector3(W, Y, Z);
            set
            {
                W = value.X;
                Y = value.Y;
                Z = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Wzx
        {
            readonly get => new Vector3(W, Z, X);
            set
            {
                W = value.X;
                Z = value.Y;
                X = value.Z;
            }
        }

        [XmlIgnore]
        public Vector3 Wzy
        {
            readonly get => new Vector3(W, Z, Y);
            set
            {
                W = value.X;
                Z = value.Y;
                Y = value.Z;
            }
        }

        [XmlIgnore]
        public Vector4 Xywz
        {
            readonly get => new Vector4(X, Y, W, Z);
            set
            {
                X = value.X;
                Y = value.Y;
                W = value.Z;
                Z = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Xzyw
        {
            readonly get => new Vector4(X, Z, Y, W);
            set
            {
                X = value.X;
                Z = value.Y;
                Y = value.Z;
                W = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Xzwy
        {
            readonly get => new Vector4(X, Z, W, Y);
            set
            {
                X = value.X;
                Z = value.Y;
                W = value.Z;
                Y = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Xwyz
        {
            readonly get => new Vector4(X, W, Y, Z);
            set
            {
                X = value.X;
                W = value.Y;
                Y = value.Z;
                Z = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Xwzy
        {
            readonly get => new Vector4(X, W, Z, Y);
            set
            {
                X = value.X;
                W = value.Y;
                Z = value.Z;
                Y = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Yxzw
        {
            readonly get => new Vector4(Y, X, Z, W);
            set
            {
                Y = value.X;
                X = value.Y;
                Z = value.Z;
                W = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Yxwz
        {
            readonly get => new Vector4(Y, X, W, Z);
            set
            {
                Y = value.X;
                X = value.Y;
                W = value.Z;
                Z = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Yyzw
        {
            readonly get => new Vector4(Y, Y, Z, W);
            set
            {
                X = value.X;
                Y = value.Y;
                Z = value.Z;
                W = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Yywz
        {
            readonly get => new Vector4(Y, Y, W, Z);
            set
            {
                X = value.X;
                Y = value.Y;
                W = value.Z;
                Z = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Yzxw
        {
            readonly get => new Vector4(Y, Z, X, W);
            set
            {
                Y = value.X;
                Z = value.Y;
                X = value.Z;
                W = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Yzwx
        {
            readonly get => new Vector4(Y, Z, W, X);
            set
            {
                Y = value.X;
                Z = value.Y;
                W = value.Z;
                X = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Ywxz
        {
            readonly get => new Vector4(Y, W, X, Z);
            set
            {
                Y = value.X;
                W = value.Y;
                X = value.Z;
                Z = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Ywzx
        {
            readonly get => new Vector4(Y, W, Z, X);
            set
            {
                Y = value.X;
                W = value.Y;
                Z = value.Z;
                X = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Zxyw
        {
            readonly get => new Vector4(Z, X, Y, W);
            set
            {
                Z = value.X;
                X = value.Y;
                Y = value.Z;
                W = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Zxwy
        {
            readonly get => new Vector4(Z, X, W, Y);
            set
            {
                Z = value.X;
                X = value.Y;
                W = value.Z;
                Y = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Zyxw
        {
            readonly get => new Vector4(Z, Y, X, W);
            set
            {
                Z = value.X;
                Y = value.Y;
                X = value.Z;
                W = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Zywx
        {
            readonly get => new Vector4(Z, Y, W, X);
            set
            {
                Z = value.X;
                Y = value.Y;
                W = value.Z;
                X = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Zwxy
        {
            readonly get => new Vector4(Z, W, X, Y);
            set
            {
                Z = value.X;
                W = value.Y;
                X = value.Z;
                Y = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Zwyx
        {
            readonly get => new Vector4(Z, W, Y, X);
            set
            {
                Z = value.X;
                W = value.Y;
                Y = value.Z;
                X = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Zwzy
        {
            readonly get => new Vector4(Z, W, Z, Y);
            set
            {
                X = value.X;
                W = value.Y;
                Z = value.Z;
                Y = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Wxyz
        {
            readonly get => new Vector4(W, X, Y, Z);
            set
            {
                W = value.X;
                X = value.Y;
                Y = value.Z;
                Z = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Wxzy
        {
            readonly get => new Vector4(W, X, Z, Y);
            set
            {
                W = value.X;
                X = value.Y;
                Z = value.Z;
                Y = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Wyxz
        {
            readonly get => new Vector4(W, Y, X, Z);
            set
            {
                W = value.X;
                Y = value.Y;
                X = value.Z;
                Z = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Wyzx
        {
            readonly get => new Vector4(W, Y, Z, X);
            set
            {
                W = value.X;
                Y = value.Y;
                Z = value.Z;
                X = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Wzxy
        {
            readonly get => new Vector4(W, Z, X, Y);
            set
            {
                W = value.X;
                Z = value.Y;
                X = value.Z;
                Y = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Wzyx
        {
            readonly get => new Vector4(W, Z, Y, X);
            set
            {
                W = value.X;
                Z = value.Y;
                Y = value.Z;
                X = value.W;
            }
        }

        [XmlIgnore]
        public Vector4 Wzyw
        {
            readonly get => new Vector4(W, Z, Y, W);
            set
            {
                X = value.X;
                Z = value.Y;
                Y = value.Z;
                W = value.W;
            }
        }

        [Pure]
        public static Vector4 operator +(Vector4 left, Vector4 right)
        {
            left.X += right.X;
            left.Y += right.Y;
            left.Z += right.Z;
            left.W += right.W;
            return left;
        }

        [Pure]
        public static Vector4 operator -(Vector4 left, Vector4 right)
        {
            left.X -= right.X;
            left.Y -= right.Y;
            left.Z -= right.Z;
            left.W -= right.W;
            return left;
        }

        [Pure]
        public static Vector4 operator -(Vector4 vec)
        {
            vec.X = -vec.X;
            vec.Y = -vec.Y;
            vec.Z = -vec.Z;
            vec.W = -vec.W;
            return vec;
        }

        [Pure]
        public static Vector4 operator *(Vector4 vec, float scale)
        {
            vec.X *= scale;
            vec.Y *= scale;
            vec.Z *= scale;
            vec.W *= scale;
            return vec;
        }

        [Pure]
        public static Vector4 operator *(float scale, Vector4 vec)
        {
            vec.X *= scale;
            vec.Y *= scale;
            vec.Z *= scale;
            vec.W *= scale;
            return vec;
        }

        [Pure]
        public static Vector4 operator *(Vector4 vec, Vector4 scale)
        {
            vec.X *= scale.X;
            vec.Y *= scale.Y;
            vec.Z *= scale.Z;
            vec.W *= scale.W;
            return vec;
        }

        [Pure]
        public static Vector4 operator *(Vector4 vec, Matrix4 mat)
        {
            TransformRow(in vec, in mat, out Vector4 result);
            return result;
        }

        [Pure]
        public static Vector4 operator *(Matrix4 mat, Vector4 vec)
        {
            TransformColumn(in mat, in vec, out Vector4 result);
            return result;
        }

        [Pure]
        public static Vector4 operator *(Quaternion quat, Vector4 vec)
        {
            Transform(in vec, in quat, out Vector4 result);
            return result;
        }

        [Pure]
        public static Vector4 operator /(Vector4 vec, float scale)
        {
            vec.X /= scale;
            vec.Y /= scale;
            vec.Z /= scale;
            vec.W /= scale;
            return vec;
        }

        [Pure]
        public static Vector4 operator /(Vector4 vec, Vector4 scale)
        {
            vec.X /= scale.X;
            vec.Y /= scale.Y;
            vec.Z /= scale.Z;
            vec.W /= scale.W;
            return vec;
        }

        [Pure]
        public static Vector4b operator <(Vector4 left, Vector4 right)
        {
            return LessThan(left, right);
        }

        [Pure]
        public static Vector4b operator <=(Vector4 left, Vector4 right)
        {
            return LessThanOrEqual(left, right);
        }

        [Pure]
        public static Vector4b operator >(Vector4 left, Vector4 right)
        {
            return GreaterThan(left, right);
        }

        [Pure]
        public static Vector4b operator >=(Vector4 left, Vector4 right)
        {
            return GreaterThanOrEqual(left, right);
        }

        public static bool operator ==(Vector4 left, Vector4 right)
        {
            return left.Equals(right);
        }

        public static bool operator !=(Vector4 left, Vector4 right)
        {
            return !(left == right);
        }

        [Pure]
        public static unsafe explicit operator float*(Vector4 v)
        {
            return &v.X;
        }

        [Pure]
        public static explicit operator IntPtr(Vector4 v)
        {
            unsafe
            {
                return (IntPtr)(&v.X);
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        [Pure]
        public static explicit operator Color4(Vector4 v)
        {
            return Unsafe.As<Vector4, Color4>(ref v);
        }

        [Pure]
        public static implicit operator Vector4d(Vector4 vec)
        {
            return new Vector4d(vec.X, vec.Y, vec.Z, vec.W);
        }

        [Pure]
        public static explicit operator Vector4h(Vector4 vec)
        {
            return new Vector4h(vec.X, vec.Y, vec.Z, vec.W);
        }

        [Pure]
        public static explicit operator Vector4i(Vector4 vec)
        {
            return new Vector4i((int)vec.X, (int)vec.Y, (int)vec.Z, (int)vec.W);
        }

        [Pure]
        public static implicit operator Vector4((float X, float Y, float Z, float W) values)
        {
            return new Vector4(values.X, values.Y, values.Z, values.W);
        }

        [Pure]
        public static explicit operator Vector4(System.Numerics.Vector4 vec)
        {
            return Unsafe.As<System.Numerics.Vector4, Vector4>(ref vec);
        }

        [Pure]
        public static explicit operator System.Numerics.Vector4(Vector4 vec)
        {
            return Unsafe.As<Vector4, System.Numerics.Vector4>(ref vec);
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
            return string.Format(
                "({0}{4} {1}{4} {2}{4} {3})",
                X.ToString(format, formatProvider),
                Y.ToString(format, formatProvider),
                Z.ToString(format, formatProvider),
                W.ToString(format, formatProvider),
                MathHelper.GetListSeparator(formatProvider));
        }

        public override readonly bool Equals(object obj)
        {
            return obj is Vector4 && Equals((Vector4)obj);
        }

        public readonly bool Equals(Vector4 other)
        {
            return X == other.X &&
                   Y == other.Y &&
                   Z == other.Z &&
                   W == other.W;
        }

        public override readonly int GetHashCode()
        {
            return HashCode.Combine(X, Y, Z, W);
        }

        [Pure]
        public readonly void Deconstruct(out float x, out float y, out float z, out float w)
        {
            x = X;
            y = Y;
            z = Z;
            w = W;
        }
    }
}
