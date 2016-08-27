#include <stdio.h>
#include <inttypes.h>

#include <bloom_filter.h>

int main()
{
	struct bloom_filter *bf;
	BLOOM_INIT(bf);

	int32_t data[] = { 42, 4, 8, 7, 3, 2 };
	size_t len = sizeof data / sizeof data[0];
	printf("set: ");
	for (size_t i = 0; i < len; i++) {
		bloom_insert_int(bf, data[i]);
		printf("%c%" PRId32 "%c",
				(i == 0) ? '[' : ' ',
				data[i],
				(i+1 >= len) ? ']' : ',');
	}
	printf("\n");

	int32_t data2[] = { 42, 7, 6, 1, 0, -4, 8 };
	size_t len2 = sizeof data2 / sizeof data2[0];
	for (size_t i = 0; i < len2; i++) {
		printf("% 3" PRId32 " in set?: %s\n",
				data2[i],
				bloom_query_int(bf, data2[i]) ? "true" : "false" );
	}

	BLOOM_FREE(bf);

}
