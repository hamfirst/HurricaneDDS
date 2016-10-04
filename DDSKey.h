#pragma once

using DDSKey = unsigned long long;

struct DDSKeyRange
{
  DDSKey m_Min;
  DDSKey m_Max;
};

static const DDSKey kMinKey = 0x0000000000000000;
static const DDSKey kMaxKey = 0xFFFFFFFFFFFFFFFF;

DDSKey GetKeyRangeSize(DDSKeyRange range);
bool InvertKeyRange(DDSKeyRange range, DDSKeyRange & out);
bool KeyInKeyRange(DDSKey key, DDSKeyRange range);
bool KeyRangeEntirelyInKeyRange(DDSKeyRange outer, DDSKeyRange inner);
bool KeyRangeOverlapsKeyRange(DDSKeyRange a, DDSKeyRange b);
bool CombineKeyRange(DDSKeyRange from, DDSKeyRange to, DDSKeyRange & out);

int GetKeyRangeDifference(DDSKeyRange a, DDSKeyRange b, DDSKeyRange & out1, DDSKeyRange & out2);
int GetKeyRangeUnion(DDSKeyRange a, DDSKeyRange b, DDSKeyRange & out1, DDSKeyRange & out2);
int GetKeyRangeIntersection(DDSKeyRange a, DDSKeyRange b, DDSKeyRange & out1, DDSKeyRange & out2);