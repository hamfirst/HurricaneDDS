
#include "DDSKey.h"

DDSKey GetKeyRangeSize(DDSKeyRange range)
{
  return (range.m_Max >= range.m_Min ? (range.m_Max - range.m_Min) : (kMaxKey - range.m_Max + range.m_Min)) + 1;
}

bool InvertKeyRange(DDSKeyRange range, DDSKeyRange & out)
{
  if (range.m_Max + 1 == range.m_Min)
  {
    return false;
  }

  out = DDSKeyRange{ range.m_Max + 1, range.m_Min - 1 };
  return true;
}

bool KeyInKeyRange(DDSKey key, DDSKeyRange range)
{
  return range.m_Max >= range.m_Min ? (key <= range.m_Max && key >= range.m_Min) : (key <= range.m_Min || key >= range.m_Max);
}

bool KeyRangeEntirelyInKeyRange(DDSKeyRange outer, DDSKeyRange inner)
{
  if (outer.m_Max + 1 == outer.m_Min)
  {
    return true;
  }

  // Check if the "inner" wraps around
  if (inner.m_Max - outer.m_Min < inner.m_Min - outer.m_Min)
  {
    return false;
  }

  if (outer.m_Max - outer.m_Min < inner.m_Min - outer.m_Min)
  {
    return false;
  }

  if (outer.m_Max - outer.m_Min < inner.m_Max - outer.m_Min)
  {
    return false;
  }

  return true;
}

bool KeyRangeOverlapsKeyRange(DDSKeyRange a, DDSKeyRange b)
{
  DDSKeyRange b_inv;
  if (InvertKeyRange(b, b_inv) == false)
  {
    return true;
  }

  return KeyRangeEntirelyInKeyRange(a, b_inv) == false;
}

bool CombineKeyRange(DDSKeyRange from, DDSKeyRange to, DDSKeyRange & out)
{
  if (from.m_Max + 1 == from.m_Min)
  {
    out = from;
    return true;
  }

  if (to.m_Max + 1 == to.m_Min)
  {
    out = to;
    return true;
  }

  DDSKeyRange start = from;
  DDSKeyRange other = to;

  if (other.m_Min - start.m_Min > start.m_Max - start.m_Min)
  {
    start = to;
    other = from;

    if (other.m_Min - start.m_Min > start.m_Max - start.m_Min)
    {
      return false;
    }
  }

  DDSKeyRange start_inv;
  InvertKeyRange(start, start_inv);
  if (KeyRangeEntirelyInKeyRange(other, start_inv))
  {
    out = DDSKeyRange{ kMinKey, kMaxKey };
  }
  else if (start.m_Max - start.m_Min < other.m_Max - start.m_Min)
  {
    out = DDSKeyRange{ start.m_Min, other.m_Max };
  }
  else
  {
    out = start;
  }

  return true;
}

int GetKeyRangeDifference(DDSKeyRange a, DDSKeyRange b, DDSKeyRange & out1, DDSKeyRange & out2)
{
  if (b.m_Max + 1 == b.m_Min)
  {
    return 0;
  }

  if (b.m_Max - a.m_Min < b.m_Min - a.m_Min)
  {
    if (a.m_Max - a.m_Min <= b.m_Max - a.m_Min)
    {
      return 0;
    }

    if (a.m_Max - a.m_Min < b.m_Min - a.m_Min)
    {
      out1 = DDSKeyRange{ b.m_Max + 1, a.m_Max };
    }
    else
    {
      out1 = DDSKeyRange{ b.m_Max + 1, b.m_Min - 1 };
    }

    return 1;
  }

  if (a.m_Max - a.m_Min < b.m_Min - a.m_Min)
  {
    out1 = a;
    return 1;
  }

  if (a.m_Min == b.m_Min)
  {
    if (a.m_Max - a.m_Min <= b.m_Max - a.m_Min)
    {
      return 0;
    }

    out1 = DDSKeyRange{ b.m_Min + 1, a.m_Max };
    return 1;
  }

  if (a.m_Max - a.m_Min <= b.m_Max - a.m_Min)
  {
    out1 = DDSKeyRange{ a.m_Min, b.m_Min - 1 };
    return 1;
  }

  out1 = DDSKeyRange{ a.m_Min, b.m_Min - 1 };
  out2 = DDSKeyRange{ b.m_Max + 1, a.m_Max };
  return 2;
}

int GetKeyRangeUnion(DDSKeyRange a, DDSKeyRange b, DDSKeyRange & out1, DDSKeyRange & out2)
{
  if (CombineKeyRange(a, b, out1))
  {
    return 1;
  }

  out1 = a;
  out2 = b;
  return 2;
}

int GetKeyRangeIntersection(DDSKeyRange a, DDSKeyRange b, DDSKeyRange & out1, DDSKeyRange & out2)
{
  DDSKeyRange inv_b;
  if (!InvertKeyRange(b, inv_b))
  {
    out1 = a;
    return 1;
  }

  return GetKeyRangeDifference(a, inv_b, out1, out2);
}