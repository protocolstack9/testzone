#include <stdio.h>
#include <stdlib.h>

void *f_memmove(void *dest, const void *src, size_t n)
{
	char *s1 = (char *)dest;
	char *s2 = (char *)src;

	// assert(dest && src)
	if (dest < src)
		while (n--)
			*s1++ = *s2++;
	else
		while (n--)
			s1[n] = s2[n];

	return dest;
}

char *f_strncpy(char *dest, const char *src, size_t n)
{
	// assert (dest && src);
	char *ptr = dest;
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for ( ; i < n; i++)
		dest[i] = '\0';

	return dest;
}

int f_strcmp(const char *s1, const char *s2)
{
	int ret = 0;
	int i;

	// assert(s1 && s2)
	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
		if (s1[i] != s2[i])
			break;

	ret = s1[i] - s2[i];

	return (ret > 0) ? 1 : (ret < 0) ? -1 : 0;
}

size_t f_strlen(const char *s)
{
	size_t len = 0;
	// assert (s != NULL)
	while (*s++ != '\0')
		len++;

	return len;
}

void f_swap_v1 (char *p, char *q)
{
	char tmp = *p ^ *q;
	*p ^= tmp;
	*q ^= tmp;
}

void f_swap_v2 (char *p, char *q)
{
	char tmp = *p;

	tmp = *p;
	*p = *q;
	*q = tmp;
}


/* another solution: using stack */
char *f_strrev(char *s)
{
	int len = f_strlen(s);
	int i;

	for (i = 0; i < len/2; i++)
		f_swap_v1(&s[i], &s[len-i-1]);
	
	return s;
}

// 1. rot를 구한다.
// 1-1. rot = rot % n;
// 1-2. 음수일 때 rot = n - rot
//		-16 % 5 = -1;
// 2. 임시버퍼를 준비한다.
// 3. 임시버퍼에 복사한다.
// 3-1. 0부터 (n-rot)만큼 rot에 복사한다.
// 3-2. n-rot부터 rot만큼 0에 복사한다.
// 4. 원본버퍼에 다시 복사한다.
char *f_rotate(char *s, int rot)
{
	int n = f_strlen(s);
	int i;
	char *p;
	// assert (s);
	
	rot = rot % n;
	if (rot < 0)
		rot = n + rot;

	p = malloc (n);
	if (!p)
		return NULL;

	f_strncpy (&p[rot], &s[0], n-rot);
	f_strncpy (&p[0], &s[n-rot], rot);

	f_strncpy (s, p, n);

	free (p);
	
	return s;
}

char *f_strcat(char *dest, const char *src)
{
	char *s1 = dest, *s2 = (char *)src;
	// assert (dest != NULL && src != NULL);
	while (*s1 != '\0')
		s1++;

	while (*s2 != '\0')
		*s1++ = *s2++;

	*s1 = '\0';

	return dest;
}


int main(void)
{
	char str1[] = "0123456789abcdefghijklmn";
	char str2[] = "0123456789abcdefghijklmn";
	char str3[] = "abcde";
	char str4[10] = "111111111";
	char str5[] = "12345";
	char buf[10] = "11";

	printf("before:%s\n", str1);
	f_memmove((void *)&str1[3], (void *)&str1[0], 5);
	printf("after:'%s'\n", str1);

	printf("\n");

	printf("before:%s\n", str2);
	f_memmove((void *)&str2[0], (void *)&str2[3], 5);
	printf("after:'%s'\n", str2);

	printf("\n");
	f_strncpy(&str4[1], &str3[1], 7);
	printf("strncpy: '%s'\n", str4);

	printf("\n");
	printf("strcmp: '%d'\n", f_strcmp("apple1", "apple1"));

	printf("\n");
	printf("strlen: '%d'\n", f_strlen(str1));

	printf("\n");
	printf("strrev: '%s'\n", f_strrev(str3));

	printf("\n");
	printf("strcat: '%s'\n", f_strcat(buf, str3));

	printf("\n");
	printf("rotate: '%s'\n", f_rotate(str5, 2));

	printf("\n");
	printf("rotate: '%s'\n", f_rotate(str5, -16));


	return 0;
}
