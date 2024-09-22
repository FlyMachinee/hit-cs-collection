#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

#define MKIMG 0

#define ROWS 8192
#define COLS 5120

long img[ROWS + 2][COLS + 2];

int make_img() {
	FILE* fp = NULL;
	fp = fopen("./img.bin", "wb");
	int cnt = 0, line[COLS + 1];
	if (fp) {
		for (int i = 1; i <= ROWS; ++i) {
			for (int j = 1; j <= COLS; ++j)
				line[j] = cnt++ + rand() - RAND_MAX / 2;
			fwrite(line + 1, sizeof(long), COLS, fp);
		}
		fclose(fp);
		return 0;
	}
	return 1;
}

int read_img() {
	FILE* fp = NULL;
	fp = fopen("./img.bin", "rb");
	if (fp) {
		for (int i = 1; i <= ROWS; ++i)
			fread(img[i] + 1, sizeof(long), COLS, fp);
		fclose(fp);
		return 0;
	}
	return 1;
}

void show_img(int n) {
	// 展示img的前n行，前n列
	for (int i = 1; i <= n && i <= ROWS; ++i) {
		for (int j = 1; j <= n && j <= COLS; ++j) {
			printf("%d\t", img[i][j]);
		}
		puts("...\n");
	}
	puts("...\t...\t...\n");
}

#if MKIMG // MKIMG = 1

int main() {
	if (make_img()) {
		printf("Image make failed\n");
		return 1;
	}
	printf("Image make succeeded\n");
	return 0;
}

#else // MKIMG = 0

void prototype();
void code_move();
void bitwise_op();
void loop_unroll();
void AVX2();
void cache();
void bitwise_op_entire_buffer();

int main() {
	if (read_img()) {
		puts("Image open failed");
		return 1;
	}
	puts("Image open succeeded");

	puts("Function: cache");

	int sum = 0, times = 50;

	for (int i = 0; i < times; ++i) {
		// show_img(10);
		clock_t begin = clock();
		cache();
		clock_t end = clock();
		// show_img(10);
	
		printf("Algorithm runs for %d ms\n", end - begin);
		sum += end - begin;
	}
	printf("Avg for %d ms\n", sum / times);

	return 0;
}

void prototype() {
	// 两行缓存，缓存图片计算结果
	long (*buffer)[COLS + 2] = malloc(sizeof(long) * 2 * (COLS + 2));

	if (!buffer) {
		puts("Not enough memory");
		exit(1);
	}

	int i;
	for (i = 1; i <= ROWS; ++i) {
		// 对第i行进行运算，保存在buffer[i%2]中
		for (int j = 1; j <= COLS; ++j) {
			buffer[i % 2][j] = (img[i - 1][j] + img[i + 1][j] + img[i][j - 1] + img[i][j + 1]) / 4;
		}
		if (i >= 2) { 
			// 第i行对第i+1行的结果也有影响，不能直接将计算结果赋值回img
			// 在第i行运算完后可以进行第i-1行运算结果的保存
			memcpy(img[i - 1] + 1, buffer[1 - i % 2] + 1, COLS * sizeof(long));
		}
	}
	// 对最后一行进行保存
	memcpy(img[i - 1] + 1, buffer[1 - i % 2] + 1, COLS * sizeof(long));
	free(buffer);
}

void code_move() {
	// 两行缓存，缓存图片计算结果
	long(*buffer)[COLS + 2] = malloc(sizeof(long) * 2 * (COLS + 2)); 

	if (!buffer) {
		puts("Not enough memory");
		exit(1);
	}

	int i, j;
	long* up = img; // 行指针上一行的头指针
	long* mid = img + 1; // 行指针的头指针
	long* down = img + 2; // 行指针下一行的头指针

	for (i = 1; i <= ROWS; ++i) {
		// 对第i行进行运算，保存在buffer[i%2]中

		for (j = 1; j <= COLS; ++j) {
			buffer[i % 2][j] = (up[j] + down[j] + mid[j - 1] + mid[j + 1]) / 4;
		}
		if (i >= 2) {
			// 第i行对第i+1行的结果也有影响，不能直接将计算结果赋值回img
			// 在第i行运算完后可以进行第i-1行运算结果的保存
			memcpy(up + 1, buffer[1 - i % 2] + 1, COLS * sizeof(long));
		}

		// 下移一行
		up += COLS + 2;
		mid += COLS + 2;
		down += COLS + 2;
	}
	// 对最后一行进行保存
	memcpy(up + 1, buffer[1 - i % 2] + 1, COLS * sizeof(long));
	free(buffer);
}

void bitwise_op() {
	// 两行缓存，缓存图片计算结果
	long(*buffer)[COLS + 2] = malloc(sizeof(long) * 2 * (COLS + 2));

	if (!buffer) {
		puts("Not enough memory");
		exit(1);
	}

	register int i, j;
	register unsigned char i_mod_2 = 0;
	register long* up = img; // 行指针上一行的头指针
	register long* mid = img + 1; // 行指针的头指针
	register long* down = img + 2; // 行指针下一行的头指针

	for (i = 1; i <= ROWS; ++i) {
		// 对第i行进行运算，保存在buffer[i%2]中
		// i%2 实际上不需要由i计算，只需要进行1->0->1->0的交替变换

		for (j = 1; j <= COLS; ++j) {
			buffer[i_mod_2][j] = (up[j] + down[j] + mid[j - 1] + mid[j + 1]) >> 2;
		}

		i_mod_2 ^= 1;
		if (i & 0xFFFE) {
			// 第i行对第i+1行的结果也有影响，不能直接将计算结果赋值回img
			// 在第i行运算完后可以进行第i-1行运算结果的保存
			memcpy(up + 1, buffer[i_mod_2] + 1, COLS * sizeof(long));
		}

		// 下移一行
		up += COLS + 2;
		mid += COLS + 2;
		down += COLS + 2;
	}
	// 对最后一行进行保存
	memcpy(up + 1, buffer[i_mod_2 ^ 1] + 1, COLS * sizeof(long));
	free(buffer);
}

void loop_unroll() {
	// 八行缓存，缓存图片计算结果
	long(*buffer)[COLS + 2] = malloc(sizeof(long) * 8 * (COLS + 2));

	if (!buffer) {
		puts("Not enough memory");
		exit(1);
	}

	register int i, j;
	long* line_1 = img; // 行指针的头指针
	long* line_2 = img + 1; // 行指针的头指针
	long* line_3 = img + 2; // 行指针的头指针
	long* line_4 = img + 3; // 行指针的头指针
	long* line_5 = img + 4; // 行指针的头指针
	long* line_6 = img + 5; // 行指针的头指针

	// 用于实现交替指向 buf 的 key 值，是对 i_mod_2 的拓展
	register unsigned char key0 = 0;
	register unsigned char key1 = 1;
	register unsigned char key2 = 2;
	register unsigned char key3 = 3;

	for (i = 1; i <= ROWS; i += 4) {
		// 1,2,3,4 行 保存在 buf[0],buf[1],buf[2],buf[3]
		// 5,6,7,8 行 保存在 buf[5],buf[6],buf[7],buf[8]
		// 9,10,11,12 行 保存在 buf[0],buf[1],buf[2],buf[3]
		// ......

		for (j = 1; j <= COLS; j += 1) {
			// 循环展开
			buffer[key0][j] = (line_1[j] + line_3[j] + line_2[j - 1] + line_2[j + 1]) >> 2;
			buffer[key1][j] = (line_2[j] + line_4[j] + line_3[j - 1] + line_3[j + 1]) >> 2;
			buffer[key2][j] = (line_3[j] + line_5[j] + line_4[j - 1] + line_4[j + 1]) >> 2;
			buffer[key3][j] = (line_4[j] + line_6[j] + line_5[j - 1] + line_5[j + 1]) >> 2;
		}
		
		// 将第三位反转：0,1,2,3 <=> 4,5,6,7
		key0 ^= 4;
		key1 ^= 4;
		key2 ^= 4;
		key3 ^= 4;

		if (i & 0xFFFE) {
			memcpy(line_1, buffer[key0], COLS * sizeof(long));
			memcpy(line_2 + 1, buffer[key1] + 1, COLS * sizeof(long));
			memcpy(line_3 + 1, buffer[key2] + 1, COLS * sizeof(long));
			memcpy(line_4 + 1, buffer[key3] + 1, COLS * sizeof(long));
		}

		// 下移一行
		line_1 += COLS + 2;
		line_2 += COLS + 2;
		line_3 += COLS + 2;
		line_4 += COLS + 2;
		line_5 += COLS + 2;
		line_6 += COLS + 2;
	}
	
	memcpy(line_1 + 1, buffer[key0] + 1, COLS * sizeof(long));
	memcpy(line_2 + 1, buffer[key1] + 1, COLS * sizeof(long));
	memcpy(line_3 + 1, buffer[key2] + 1, COLS * sizeof(long));
	memcpy(line_4 + 1, buffer[key3] + 1, COLS * sizeof(long));
	free(buffer);
}

#include <intrin.h>

void AVX2() {
	// 使用AVX2指令集，每次对 8 个四字节(即64位)的long进行运算

	// 两行缓存，缓存图片计算结果
	long(*buffer)[COLS + 2] = malloc(sizeof(long) * 2 * (COLS + 2));

	if (!buffer) {
		puts("Not enough memory");
		exit(1);
	}

	register int i, j;
	register unsigned char i_mod_2 = 0;
	register long* up = img; // 行指针上一行的头指针
	register long* mid = img + 1; // 行指针的头指针
	register long* down = img + 2; // 行指针下一行的头指针

	__m256i vec_l, vec_r, vec_u, vec_d;

	for (i = 1; i <= ROWS; ++i) {
		// 对第i行进行运算，保存在buffer[i%2]中
		// i%2 实际上不需要由i计算，只需要进行1->0->1->0的交替变换

		for (j = 1; j <= COLS; j += 8) {
			// 向量加载
			vec_l = _mm256_loadu_si256(mid + j - 1);
			vec_r = _mm256_loadu_si256(mid + j + 1);
			vec_u = _mm256_loadu_si256(up + j);
			vec_d = _mm256_loadu_si256(down + j);

			// 向量加法
			vec_l = _mm256_add_epi32(vec_l, vec_r);
			vec_u = _mm256_add_epi32(vec_u, vec_d);
			vec_l = _mm256_add_epi32(vec_l, vec_u);

			// 有符号右移
			*((__m256i*)(&buffer[i_mod_2][j])) = _mm256_srai_epi32(vec_l, 2);
		}

		i_mod_2 ^= 1;
		if (i & 0xFFFE) {
			// 第i行对第i+1行的结果也有影响，不能直接将计算结果赋值回img
			// 在第i行运算完后可以进行第i-1行运算结果的保存
			memcpy(up + 1, buffer[i_mod_2] + 1, COLS * sizeof(long));
		}

		// 下移一行
		up += COLS + 2;
		mid += COLS + 2;
		down += COLS + 2;
	}
	// 对最后一行进行保存
	memcpy(up + 1, buffer[i_mod_2 ^ 1] + 1, COLS * sizeof(long));
	free(buffer);
}

void cache() {

	// 为了实现对cache的优化，同时保证结果的准确性以及代码的简洁，需要将整个图片的计算结果进行缓存
	long(*buffer)[COLS + 2] = malloc(sizeof(long) * (ROWS + 2) * (COLS + 2));

	if (!buffer) {
		puts("Not enough memory");
		exit(1);
	}

	register int i, j, k;
	
	for (k = 1; k <= COLS; k += 16) {
		register long* up = img; // 行指针上一行的头指针
		register long* mid = img + 1; // 行指针的头指针
		register long* down = img + 2; // 行指针下一行的头指针

		for (i = 1; i <= ROWS; ++i) {

			long* buf = buffer + i;
			for (j = k; j <= k + 16; ++j) {
				buf[j] = (up[j] + down[j] + mid[j - 1] + mid[j + 1]) >> 2;
			}

			// 下移一行
			up += COLS + 2;
			mid += COLS + 2;
			down += COLS + 2;
		}
	}

	memcpy(img, buffer, sizeof(long) * (ROWS + 2) * (COLS + 2));
	free(buffer);
}

void bitwise_op_entire_buffer() {

	long(*buffer)[COLS + 2] = malloc(sizeof(long) * (ROWS + 2) * (COLS + 2));

	if (!buffer) {
		puts("Not enough memory");
		exit(1);
	}

	register int i, j;
	register long* up = img; // 行指针上一行的头指针
	register long* mid = img + 1; // 行指针的头指针
	register long* down = img + 2; // 行指针下一行的头指针

	for (i = 1; i <= ROWS; ++i) {
		// 对第i行进行运算，保存在buffer[i%2]中
		// i%2 实际上不需要由i计算，只需要进行1->0->1->0的交替变换
		long* buf = buffer + i;
		for (j = 1; j <= COLS; ++j) {
			buf[j] = (up[j] + down[j] + mid[j - 1] + mid[j + 1]) >> 2;
		}

		// 下移一行
		up += COLS + 2;
		mid += COLS + 2;
		down += COLS + 2;
	}
	
	memcpy(img, buffer, sizeof(long) * (ROWS + 2) * (COLS + 2));
	free(buffer);
}

#endif // MKIMG