
namespace utils
{

struct Range
{
	float start, end;
};

/*
* Maps value within one range to another using linear transformation
*/
float MapRangeLinearly(float val, Range source, Range target);

}
