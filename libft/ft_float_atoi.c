
#include "libft.h"

static int				isnonprint(int c)
{
	if (c == '\t' || c == '\v' || c == '\f' ||
		c == '\r' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

int	offset_neg(const char *str, int *ext_i)
{
	int	negativity;
	int				i;

	i = 0;
	negativity = 0;
	while (isnonprint((int)str[i]) == 1)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negativity = 1;
		i++;
	}
	*ext_i = i;
	return (negativity);
}

float					ft_float_atoi(const char *str)
{
	int				i;
	int				d_after_point;
	int				is_neg;
	float			result;

	is_neg = offset_neg(str, &i) ;
	result = 0.0;
	d_after_point = 0;
	while (ft_isdigit((int)str[i]) || (str[i] == '.' && !d_after_point))
	{
		if (str[i] == '.')
		{
			d_after_point = 10;
			i++;
			continue ;
		}
		if (!d_after_point)
			result = (result * 10) + (float)(str[i] - '0');
		else
		{
			result += ((float)(str[i] - '0')) / d_after_point;
			d_after_point *= 10;
		}
		i++;
	}
	result = is_neg ? -result : result;
	return (result);
}



// int main()
// {
// 	float test = ft_float_atoi("  -333ddd12.3456789");
// 	float test2 = -33312.3456789;
// 	printf("%f   %f \n", test, test2);
// }