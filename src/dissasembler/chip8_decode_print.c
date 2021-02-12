#include "../../includes/chip8.h"
#include <stdlib.h>
#include <strings.h>

char	*ft_itoa_base(int n, int base){
	const char *basestr = "0123456789abcdef";
	static char ret[50];
	int i = 0;
	int j = 0;
	int sign;

	bzero(ret, 50);
	if (!(base >= 2 && base <= 16))		// check base
		return (NULL);

	if (n < 0){				// check neg & get abs
		sign = -1;
		n *= -1;
	}

	while (n){				// convert
		ret[i] = basestr[abs(n % base)];
		n /= base;
		i++;
	}

	if (sign == -1 && base == 10){		// check sign & base to get that - in if need be
		ret[i] = '-';
		i++;
	}
	ret[i] = 0;				// null terminate str

	i--;					// go back for the last char
	while (j < i){				// rev string  
		char tmp;
		tmp = ret[j];
		ret[j] = ret[i];
		ret[i] = tmp;
		j++;
		i--;
	}

	return (&ret[0]);			// return pointer to 1st element
}
