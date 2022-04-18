#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct head
{
	unsigned char type;
	unsigned int len;
} head;

typedef struct
{
	head *header;
	void *data;
} data_structure;

int add_last(void **arr, int *len, data_structure *data)
{

	char *input = (char *)calloc(256, sizeof(char));
	int type;

	// ALOCATE MEMEORY FOR EVERY STRUCTURE
	data = (data_structure *)malloc(sizeof(data_structure));
	data->header = (head *)malloc(sizeof(head));
	data->header->len = 0;

	scanf("%d", &type);
	scanf("%s", input);

	// TAKE EACK TYPE
	if (type == 1)
	{
		data->header->type = (unsigned char)'1';

		// primul string
		data->header->len += strlen(input) + 1;
		data->data = malloc(data->header->len);
		memcpy(data->data, input, strlen(input) + 1);

		// bancnota 1
		int8_t bancnota_1;
		scanf("%hhd", &bancnota_1);
		data->data = realloc(data->data, data->header->len + sizeof(int8_t));
		memcpy(data->data + data->header->len, &bancnota_1, sizeof(int8_t));
		data->header->len += 1;

		// test 2
		// bancnota 2
		int8_t bancnota_2;
		scanf("%hhd", &bancnota_2);
		data->data = realloc(data->data, data->header->len + sizeof(int8_t));
		memcpy(data->data + data->header->len, &bancnota_2, sizeof(int8_t));
		data->header->len += 1;

		// pentru al doilea string
		scanf("%s", input);
		data->data = realloc(data->data, data->header->len + strlen(input) + 1);
		memcpy(data->data + data->header->len, input, strlen(input) + 1);
		data->header->len += strlen(input) + 1;
	}
	else if (type == 2)
	{
		data->header->type = (unsigned char)'2';

		// primul string
		data->header->len += strlen(input) + 1;
		data->data = malloc(data->header->len);
		memcpy(data->data, input, strlen(input) + 1);

		// bancnota 1
		int16_t bancnota_1;
		scanf("%hd\n", &bancnota_1);
		data->data = realloc(data->data, data->header->len + sizeof(int16_t));
		memcpy(data->data + data->header->len, &bancnota_1, sizeof(int16_t));
		data->header->len += 2;

		// test 2
		// bancnota 2
		int32_t bancnota_2;
		scanf("%d", &bancnota_2);
		data->data = realloc(data->data, data->header->len + sizeof(int32_t));
		memcpy(data->data + data->header->len, &bancnota_2, sizeof(int32_t));
		data->header->len += 4;

		// pentru al doilea string
		scanf("%s", input);
		data->data = realloc(data->data, data->header->len + strlen(input) + 1);
		memcpy(data->data + data->header->len, input, strlen(input) + 1);
		data->header->len += strlen(input) + 1;
	}
	else if (type == 3)
	{
		data->header->type = (unsigned char)'3';

		// primul string
		data->header->len += strlen(input) + 1;
		data->data = malloc(data->header->len);
		memcpy(data->data, input, strlen(input) + 1);

		// bancnota 1
		int32_t bancnota_1;
		scanf("%d\n", &bancnota_1);
		data->data = realloc(data->data, data->header->len + sizeof(int32_t));
		memcpy(data->data + data->header->len, &bancnota_1, sizeof(int32_t));
		data->header->len += 4;

		// test 2
		// bancnota 2
		int32_t bancnota_2;
		scanf("%d", &bancnota_2);
		data->data = realloc(data->data, data->header->len + sizeof(int32_t));
		memcpy(data->data + data->header->len, &bancnota_2, sizeof(int32_t));
		data->header->len += 4;

		// pentru al doilea string
		scanf("%s", input);
		data->data = realloc(data->data, data->header->len + strlen(input) + 1);
		memcpy(data->data + data->header->len, input, strlen(input) + 1);
		data->header->len += strlen(input) + 1;
	}

	// the new lenght
	*len = *len + sizeof(head) + data->header->len;

	if (*arr == NULL)
	{
		*arr = malloc(*len);
		// copy header
		memcpy(*arr, data->header, sizeof(head));
		// copy void pointer
		memcpy(*arr + sizeof(head), data->data, data->header->len);
	}
	else
	{
		// new size with new content
		*arr = realloc(*arr, *len);
		memcpy(*arr + *len - sizeof(head) - data->header->len, data->header, sizeof(head));
		memcpy(*arr + *len - data->header->len, data->data, data->header->len);
	}

	// take care here
	// -> boom :)
	free(data->header);
	free(data->data);
	free(data);
	free(input);
	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
	if (index < 0)
	{
		return 0;
	}

	int i_contor = 0;
	int start = 0;

	// find the number of bytes for start of you index
	while (start < *len)
	{
		i_contor++;

		int lungime = ((head *)(*arr + start))->len;

		start += sizeof(head) + lungime;
	}

	if (index > i_contor)
	{
		int temp_val = add_last(arr, len, data);
		(void)temp_val;

		return 0;
	}
	else
	{
		int i = 0;
		int position = 0;
		while (i < index)
		{
			i++;

			int lungime = ((head *)(arr + position))->len;

			position += sizeof(head) + lungime;
		}

		char *input = (char *)calloc(256, sizeof(char));
		int type;

		data = (data_structure *)malloc(sizeof(data_structure));
		data->header = (head *)malloc(sizeof(head));
		data->header->len = 0;

		scanf("%d", &type);
		scanf("%s", input);

		// same story as above
		// i could make a function for it :)
		if (type == 1)
		{

			data->header->type = (unsigned char)'1';

			// primul string
			data->header->len = strlen(input) + 1;
			data->data = malloc(data->header->len);
			memcpy(data->data, input, strlen(input) + 1);

			// bancnota 1
			int8_t bancnota_1;
			scanf("%hhd", &bancnota_1);
			data->data = realloc(data->data, data->header->len + sizeof(int8_t));
			memcpy(data->data + data->header->len, &bancnota_1, sizeof(int8_t));
			data->header->len += 1;

			// bancnota 2
			int8_t bancnota_2;
			scanf("%hhd", &bancnota_2);
			data->data = realloc(data->data, data->header->len + sizeof(int8_t));
			memcpy(data->data + data->header->len, &bancnota_2, sizeof(int8_t));
			data->header->len += 1;

			// pentru al doilea string
			scanf("%s", input);
			data->data = realloc(data->data, data->header->len + strlen(input) + 1);
			memcpy(data->data + data->header->len, input, strlen(input) + 1);
			data->header->len += strlen(input) + 1;
		}
		else if (type == 2)
		{
			data->header->type = (unsigned char)'2';

			// primul string
			data->header->len += strlen(input) + 1;
			data->data = malloc(data->header->len);
			memcpy(data->data, input, strlen(input) + 1);

			// bancnota 1
			int16_t bancnota_1;
			scanf("%hd\n", &bancnota_1);
			data->data = realloc(data->data, data->header->len + sizeof(int16_t));
			memcpy(data->data + data->header->len, &bancnota_1, sizeof(int16_t));
			data->header->len += 2;

			// test 2
			// bancnota 2
			int32_t bancnota_2;
			scanf("%d", &bancnota_2);
			data->data = realloc(data->data, data->header->len + sizeof(int32_t));
			memcpy(data->data + data->header->len, &bancnota_2, sizeof(int32_t));
			data->header->len += 4;

			// pentru al doilea string
			scanf("%s", input);
			data->data = realloc(data->data, data->header->len + strlen(input) + 1);
			memcpy(data->data + data->header->len, input, strlen(input) + 1);
			data->header->len += strlen(input) + 1;
		}
		else if (type == 3)
		{

			data->header->type = (unsigned char)'3';

			// primul string
			data->header->len += strlen(input) + 1;
			data->data = malloc(data->header->len);
			memcpy(data->data, input, strlen(input) + 1);

			//! bancnota 1
			int32_t bancnota_1;
			scanf("%d\n", &bancnota_1);
			data->data = realloc(data->data, data->header->len + sizeof(int32_t));
			memcpy(data->data + data->header->len, &bancnota_1, sizeof(int32_t));
			data->header->len += 4;

			// test 2
			// bancnota 2
			int32_t bancnota_2;
			scanf("%d", &bancnota_2);
			data->data = realloc(data->data, data->header->len + sizeof(int32_t));
			memcpy(data->data + data->header->len, &bancnota_2, sizeof(int32_t));
			data->header->len += 4;

			// pentru al doilea string
			scanf("%s", input);
			data->data = realloc(data->data, data->header->len + strlen(input) + 1);
			memcpy(data->data + data->header->len, input, strlen(input) + 1);
			data->header->len += strlen(input) + 1;
		}

		*arr = realloc(*arr, *len + sizeof(head) + data->header->len);

		void *aux = NULL;
		aux = malloc(*len - position);

		memcpy(aux, *arr + position, *len - position);

		memcpy(aux, *arr + position, *len - position);
		memcpy(*arr + position, data->header, sizeof(head));
		memcpy(*arr + position + sizeof(head), data->data, data->header->len);
		memcpy(*arr + position + sizeof(head) + data->header->len, aux, *len - position);

		*len = *len + data->header->len + sizeof(head);

		free(aux);
		free(data->header);
		free(data->data);
		free(data);
		free(input);
	}

	return 0;
}

void find(void *data_block, int len, int index)
{
	if (index > len || index < 0)
	{
		exit(0);
	}
	else
	{
		int i = 0;
		int position = 0;
		while (i < index)
		{
			i++;

			int lungime = ((head *)(data_block + position))->len;

			position += sizeof(head) + lungime;
		}

		int lungime = ((head *)(data_block + position))->len;

		void *aux = malloc(sizeof(head) + lungime);
		memcpy(aux, data_block + position, sizeof(head) + lungime);

		print(aux, sizeof(head) + lungime);

		free(aux);
	}
}

int delete_at(void **arr, int *len, int index)
{
	int i_contor = 0;
	int start = 0;
	while (i_contor < index)
	{
		i_contor++;

		int lungime = ((head *)(*arr + start))->len;

		start += sizeof(head) + lungime;
	}

	int lungime = ((head *)(*arr + start))->len;
	memcpy(*arr + start, *arr + start + sizeof(head) + lungime, *len - start - sizeof(head) - lungime);

	*arr = realloc(*arr, *len - lungime - sizeof(head));

	*len = *len - lungime - sizeof(head);
}

void print(void *arr, int len)
{
	int contor = 0;
	while (contor < len)
	{
		unsigned char type = ((head *)(arr + contor))->type;
		int lungime = ((head *)(arr + contor))->len;

		printf("Tipul %c\n", type);
		if (type == '1')
		{
			char *p = ((char *)(arr + contor + sizeof(head)));
			printf("%s pentru", p);
			printf(" %s\n", ((char *)(arr + contor + sizeof(head))) + strlen(p) + 1 + 2);

			int8_t val = *((int8_t *)(arr + contor + sizeof(head) + strlen(p) + 1));
			printf("%" PRId8 "\n", val);

			val = *((int8_t *)(arr + contor + sizeof(head) + strlen(p) + 1 + 1));
			printf("%" PRId8 "\n", val);

			printf("\n");
		}

		else if (type == '2')
		{
			char *p = ((char *)(arr + contor + sizeof(head)));
			printf("%s pentru", p);
			printf(" %s\n", (char *)(arr + contor + sizeof(head) + strlen(p) + 1 + 6));

			int16_t val = *((int16_t *)(arr + contor + sizeof(head) + strlen(p) + 1));
			printf("%" PRId16 "\n", val);

			int32_t val_aux = *((int32_t *)(arr + contor + sizeof(head) + strlen(p) + 1 + 2));
			printf("%" PRId32 "\n", val_aux);

			printf("\n");
		}
		else if (type == '3')
		{
			char *p = ((char *)(arr + contor + sizeof(head)));
			printf("%s pentru", p);
			printf(" %s\n", (char *)(arr + contor + sizeof(head) + strlen(p) + 1 + 8));

			int32_t val = *((int32_t *)(arr + contor + sizeof(head) + strlen(p) + 1));
			printf("%" PRId32 "\n", val);

			int32_t val_aux = *((int32_t *)(arr + contor + sizeof(head) + strlen(p) + 1 + 4));
			printf("%" PRId32 "\n", val_aux);

			printf("\n");
		}
		contor += sizeof(head) + lungime;
	}
}

int main()
{
	// ! the vector of bytes u have to work with =}
	// ! good luck :) => thanks, but I need more than that :)

	void *arr = NULL;
	int len = 0;
	data_structure *STRUCTURE = NULL;
	char *input = (char *)calloc(256, sizeof(char));
	int index;

	while (scanf("%s", input) != EOF)
	{
		if (strcmp(input, "insert") == 0)
		{
			int result = add_last(&arr, &len, STRUCTURE);
			(void)result;
		}
		else if (strcmp(input, "insert_at") == 0)
		{
			scanf("%d", &index);
			add_at(&arr, &len, STRUCTURE, index);
		}
		else if (strcmp(input, "find") == 0)
		{
			scanf("%d", &index);
			find(arr, len, index);
		}
		else if (strcmp(input, "print") == 0)
		{
			print(arr, len);
		}
		else if (strcmp(input, "delete_at") == 0)
		{
			scanf("%d", &index);
			int temp = delete_at(&arr, &len, index);
			(void)temp;
		}
		else if (strcmp(input, "exit") == 0)
		{
			free(input);
			free(arr);
			return 0;
		}
	}

	return 0;
}