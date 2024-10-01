/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:11:59 by hle-hena          #+#    #+#             */
/*   Updated: 2024/10/01 12:07:35 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		stop_everything(void)
{
	ft_printf("\n\n\nProgram has stopped due to wrong placeholder/flags\n");
	return (0);
}

void	init_args(t_param *args)
{
	args->flags = 0;
	args->width = 0;
	args->precision = 0;
	args->placeholder = 'q';
}

int	parse(t_param *args, char *str)
{
	int		i;
	int		flag_val;

	i = 1;
	while (str[i] && ft_strchr("#+ 0-", str[i]))
	{
		flag_val = (str[i] == '#') * 1 + (str[i] == '+')* 2 + (str[i] ==
					' ') * 4 + (str[i] == '0') * 8 + (str[i] == '-') * 16;
		if (args->flags & flag_val)
            return (i);
        args->flags += flag_val;
		i++;
	}
	(*args).width = ft_atoi(&str[i]);
	i += ft_numlen((*args).width) * ((*args).width != 0);
	if (str[i] == '.')
	{
		i ++;
		(*args).precision = ft_atoi(&str[i]) + (str[i] == '*') * (-1);
        i += ft_numlen((*args).precision) * ((*args).precision != -1);
		i += (str[i] == '*');
	}
	if (ft_strchr("cspdiuxX%", str[i]))
		(*args).placeholder = str[i];
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	t_param	args;
	int		i;
	int		written;
	int		temp;

	va_start(ap, str);
	init_args(&args);
	i = -1;
	written = 0;
	while (str[++i])
	{
		if (str[i] == '%')
		{
			i += parse(&args, (char *)(&str[i]));
			if (args.placeholder == 'q')
				return (stop_everything());
			if ((temp = handle_args(args, ap)) == 0)
				return (stop_everything());
			written += temp;
		}
		else
			written += ft_putchar_fd(str[i], 1);
	}
	return (va_end(ap), written);
}

//Should a .* with only one value after give out an output ?
//ft_printf("Test 30: |%.0u|\n", 0);
/* int main()
{
	int	test = 2147483647;
	ft_printf("Hello '%00.*u'\n", 14, test);
} */


/* #include <limits.h>

int main(void)
{
    // 1. Basic Tests for %d and %i
    ft_printf("Val is '%d'\n", ft_printf("Test 1: |%d|\n", 42));      // Expected: |42|
    ft_printf("Val is '%d'\n", ft_printf("Test 2: |%i|\n", -42));     // Expected: |-42|
    ft_printf("Val is '%d'\n", ft_printf("Test 3: |%d|\n", 0));       // Expected: |0|
    ft_printf("Val is '%d'\n", ft_printf("Test 4: |%i|\n", INT_MAX)); // Expected: |2147483647|
    ft_printf("Val is '%d'\n", ft_printf("Test 5: |%i|\n", INT_MIN)); // Expected: |-2147483648|

    // 2. With '+' Flag for %d and %i
    ft_printf("Val is '%d'\n", ft_printf("Test 6: |%+d|\n", 42));     // Expected: |+42|
    ft_printf("Val is '%d'\n", ft_printf("Test 7: |%+i|\n", -42));    // Expected: |-42|

    // 3. With ' ' Flag for %d and %i
    ft_printf("Val is '%d'\n", ft_printf("Test 8: |% d|\n", 42));     // Expected: | 42| (Space before positive)
    ft_printf("Val is '%d'\n", ft_printf("Test 9: |% d|\n", -42));    // Expected: |-42| (No space for negative)

    // 4. With '0' Flag for %d and %i
    ft_printf("Val is '%d'\n", ft_printf("Test 10: |%05d|\n", 42));   // Expected: |00042| (5 characters, zero-padded)
    ft_printf("Val is '%d'\n", ft_printf("Test 11: |%05d|\n", -42));  // Expected: |-0042| (Minus sign + zero padding)

    // 5. With '-' Flag for %d and %i
    ft_printf("Val is '%d'\n", ft_printf("Test 12: |%-5d|\n", 42));   // Expected: |42   | (Left aligned, space-padded)
    ft_printf("Val is '%d'\n", ft_printf("Test 13: |%-5d|\n", -42));  // Expected: |-42  | (Left aligned, space-padded)

    // 6. With '#' Flag (No effect on %d and %i)
    // ft_printf("Val is '%d'\n", ft_printf("Test 14: |%#d|\n", 42));    // Expected: |42|
    // ft_printf("Val is '%d'\n", ft_printf("Test 15: |%#i|\n", -42);   // Expected: |-42|

    // 7. With Width Specifier for %d
    ft_printf("Val is '%d'\n", ft_printf("Test 16: |%10d|\n", 42));   // Expected: |        42| (Right aligned, width 10)
    ft_printf("Val is '%d'\n", ft_printf("Test 17: |%-10d|\n", -42)); // Expected: |-42       | (Left aligned, width 10)

    // 8. With Precision for %d and %i
    ft_printf("Val is '%d'\n", ft_printf("Test 18: |%.5d|\n", 42));   // Expected: |00042| (Precision 5, zero-padded)
    ft_printf("Val is '%d'\n", ft_printf("Test 19: |%.5d|\n", -42));  // Expected: |-00042| (Precision 5, zero-padded)

    // 9. Basic Tests for %u (Unsigned)
    ft_printf("Val is '%d'\n", ft_printf("Test 20: |%u|\n", 42U));          // Expected: |42|
    ft_printf("Val is '%d'\n", ft_printf("Test 21: |%u|\n", 0U));           // Expected: |0|
    ft_printf("Val is '%d'\n", ft_printf("Test 22: |%u|\n", UINT_MAX));     // Expected: |4294967295|

    // 10. With Width Specifier for %u
    ft_printf("Val is '%d'\n", ft_printf("Test 23: |%10u|\n", 42U));        // Expected: |        42|
    ft_printf("Val is '%d'\n", ft_printf("Test 24: |%-10u|\n", 42U));       // Expected: |42        |

    // 11. With '0' Flag for %u
    ft_printf("Val is '%d'\n", ft_printf("Test 25: |%010u|\n", 42U));       // Expected: |0000000042|

    // 12. With Precision for %u
    ft_printf("Val is '%d'\n", ft_printf("Test 26: |%.5u|\n", 42U));        // Expected: |00042|

    // 13. Combination of Flags for %u
    // ft_printf("Val is '%d'\n", ft_printf("Test 27: |%-010u|\n", 42U));      // Expected: |42        |

    // 14. Tests for i with flags and precision
    ft_printf("Val is '%d'\n", ft_printf("Test 28: |%+05i|\n", 42));        // Expected: |+0042|
    ft_printf("Val is '%d'\n", ft_printf("Test 29: |% 05i|\n", 42));        // Expected: | 0042|
    ft_printf("Val is '%d'\n", ft_printf("Test 30: |%.0i|\n", 0));          // Expected: || (Precision 0, no output)

    // 15. Basic Tests for %x (Hexadecimal lowercase)
    ft_printf("Val is '%d'\n", ft_printf("Test 31: |%x|\n", 255));          // Expected: |ff|
    ft_printf("Val is '%d'\n", ft_printf("Test 32: |%x|\n", 0));            // Expected: |0|
    ft_printf("Val is '%d'\n", ft_printf("Test 33: |%x|\n", UINT_MAX));     // Expected: |ffffffff|

    // 16. With '#' Flag for %x
    ft_printf("Val is '%d'\n", ft_printf("Test 34: |%#x|\n", 255));         // Expected: |0xff|

    // 17. With '0' Flag for %x
    ft_printf("Val is '%d'\n", ft_printf("Test 35: |%05x|\n", 255));        // Expected: |000ff|

    // 18. With '-' Flag for %x
    ft_printf("Val is '%d'\n", ft_printf("Test 36: |%-5x|\n", 255));        // Expected: |ff   |

    // 19. Basic Tests for %X (Hexadecimal uppercase)
    ft_printf("Val is '%d'\n", ft_printf("Test 37: |%X|\n", 255));          // Expected: |FF|
    ft_printf("Val is '%d'\n", ft_printf("Test 38: |%X|\n", 0));            // Expected: |0|
    ft_printf("Val is '%d'\n", ft_printf("Test 39: |%X|\n", UINT_MAX));     // Expected: |FFFFFFFF|

    // 20. With '#' Flag for %X
    ft_printf("Val is '%d'\n", ft_printf("Test 40: |%#X|\n", 255));         // Expected: |0XFF|

    // 21. With '0' Flag for %X
    ft_printf("Val is '%d'\n", ft_printf("Test 41: |%05X|\n", 255));        // Expected: |00FF|

    // 22. With '-' Flag for %X
    ft_printf("Val is '%d'\n", ft_printf("Test 42: |%-5X|\n", 255));        // Expected: |FF   |

    // 23. Tests for %c (Character)
    ft_printf("Val is '%d'\n", ft_printf("Test 43: |%c|\n", 'A'));          // Expected: |A|
    ft_printf("Val is '%d'\n", ft_printf("Test 44: |%5c|\n", 'A'));         // Expected: |    A|
    ft_printf("Val is '%d'\n", ft_printf("Test 45: |%-5c|\n", 'A'));        // Expected: |A    |

    // 24. Tests for %s (String)
    ft_printf("Val is '%d'\n", ft_printf("Test 46: |%s|\n", "Hello"));      // Expected: |Hello|
    ft_printf("Val is '%d'\n", ft_printf("Test 47: |%-5.3s|\n", "Hello"));    // Expected: |Hel|
    ft_printf("Val is '%d'\n", ft_printf("Test 48: |%10s|\n", "Hello"));    // Expected: |     Hello|
    ft_printf("Val is '%d'\n", ft_printf("Test 49: |%-10s|\n", "Hello"));   // Expected: |Hello     |

    // 25. Tests for %p (Pointer)
    void *ptr = (void *)0x12345;
    ft_printf("Val is '%d'\n", ft_printf("Test 50: |%p|\n", ptr));          // Expected: |0x12345|
    ft_printf("Val is '%d'\n", ft_printf("Test 51: |%20p|\n", ptr));        // Expected: |           0x12345|
    ft_printf("Val is '%d'\n", ft_printf("Test 52: |%-20p|\n", ptr));       // Expected: |0x12345            |

    // 26. Tests for %%
    ft_printf("Val is '%d'\n", ft_printf("Test 53: |%%|\n"));               // Expected: |%|
    // ft_printf("Val is '%d'\n", ft_printf(("Test 54: |%5%|\n");              // Expected: |    %|
    // ft_printf("Val is '%d'\n", ft_printf(("Test 55: |%-5%|\n");             // Expected: |%    |

    return 0;
}
 */