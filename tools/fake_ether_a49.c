#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *
 * inputs
 * ----------------
 * A0  (5) fifo_wr[0]
 * A1  (6) fifo_wr[1]
 * A2  (7) fifo_wr[2]
 * A3  (4) fifo_wr[3]
 * A4  (3) fifo_rd[0]
 * A5  (2) fifo_rd[1]
 * A6  (1) fifo_rd[2]
 * A7 (15) fifo_rd[3]
 *
 * outputs active low
 * ----------------------------
 * D0 (12) BE'    (buffer empty)
 * D1 (11) BNE'   (buffer next empty ?)
 * D2 (10) BNNE'  (buffer next next empty ?)
 * D3  (9) BF'    (buffer full)
 */
#define	BE(wr,rd)	(((wr)==(rd))?000:001)
#define	BNE(wr,rd)	(((wr)==(((rd)+1)&017))?000:002)
#define	BNNE(wr,rd)	(((wr)==(((rd)+2)&017))?000:004)
#define	BF(wr,rd)	(((((wr)+1)&017)==(rd))?000:010)
#define	B(wr,rd)	(BE(wr,rd) | BNE(wr,rd) | BNNE(wr,rd) | BF(wr,rd))

unsigned char ether_a49[256] = {
	B(000,000),B(010,000),B(004,000),B(014,000),B(002,000),B(012,000),B(006,000),B(016,000),
	B(001,000),B(011,000),B(005,000),B(015,000),B(003,000),B(013,000),B(007,000),B(017,000),
	B(000,010),B(010,010),B(004,010),B(014,010),B(002,010),B(012,010),B(006,010),B(016,010),
	B(001,010),B(011,010),B(005,010),B(015,010),B(003,010),B(013,010),B(007,010),B(017,010),
	B(000,004),B(010,004),B(004,004),B(014,004),B(002,004),B(012,004),B(006,004),B(016,004),
	B(001,004),B(011,004),B(005,004),B(015,004),B(003,004),B(013,004),B(007,004),B(017,004),
	B(000,014),B(010,014),B(004,014),B(014,014),B(002,014),B(012,014),B(006,014),B(016,014),
	B(001,014),B(011,014),B(005,014),B(015,014),B(003,014),B(013,014),B(007,014),B(017,014),
	B(000,002),B(010,002),B(004,002),B(014,002),B(002,002),B(012,002),B(006,002),B(016,002),
	B(001,002),B(011,002),B(005,002),B(015,002),B(003,002),B(013,002),B(007,002),B(017,002),
	B(000,012),B(010,012),B(004,012),B(014,012),B(002,012),B(012,012),B(006,012),B(016,012),
	B(001,012),B(011,012),B(005,012),B(015,012),B(003,012),B(013,012),B(007,012),B(017,012),
	B(000,006),B(010,006),B(004,006),B(014,006),B(002,006),B(012,006),B(006,006),B(016,006),
	B(001,006),B(011,006),B(005,006),B(015,006),B(003,006),B(013,006),B(007,006),B(017,006),
	B(000,016),B(010,016),B(004,016),B(014,016),B(002,016),B(012,016),B(006,016),B(016,016),
	B(001,016),B(011,016),B(005,016),B(015,016),B(003,016),B(013,016),B(007,016),B(017,016),
	B(000,001),B(010,001),B(004,001),B(014,001),B(002,001),B(012,001),B(006,001),B(016,001),
	B(001,001),B(011,001),B(005,001),B(015,001),B(003,001),B(013,001),B(007,001),B(017,001),
	B(000,011),B(010,011),B(004,011),B(014,011),B(002,011),B(012,011),B(006,011),B(016,011),
	B(001,011),B(011,011),B(005,011),B(015,011),B(003,011),B(013,011),B(007,011),B(017,011),
	B(000,005),B(010,005),B(004,005),B(014,005),B(002,005),B(012,005),B(006,005),B(016,005),
	B(001,005),B(011,005),B(005,005),B(015,005),B(003,005),B(013,005),B(007,005),B(017,005),
	B(000,015),B(010,015),B(004,015),B(014,015),B(002,015),B(012,015),B(006,015),B(016,015),
	B(001,015),B(011,015),B(005,015),B(015,015),B(003,015),B(013,015),B(007,015),B(017,015),
	B(000,003),B(010,003),B(004,003),B(014,003),B(002,003),B(012,003),B(006,003),B(016,003),
	B(001,003),B(011,003),B(005,003),B(015,003),B(003,003),B(013,003),B(007,003),B(017,003),
	B(000,013),B(010,013),B(004,013),B(014,013),B(002,013),B(012,013),B(006,013),B(016,013),
	B(001,013),B(011,013),B(005,013),B(015,013),B(003,013),B(013,013),B(007,013),B(017,013),
	B(000,007),B(010,007),B(004,007),B(014,007),B(002,007),B(012,007),B(006,007),B(016,007),
	B(001,007),B(011,007),B(005,007),B(015,007),B(003,007),B(013,007),B(007,007),B(017,007),
	B(000,017),B(010,017),B(004,017),B(014,017),B(002,017),B(012,017),B(006,017),B(016,017),
	B(001,017),B(011,017),B(005,017),B(015,017),B(003,017),B(013,017),B(007,017),B(017,017) 
};

int main(int argc, char **argv)
{
	FILE *fp;

	fp = fopen("ether.a49", "wb");
	if (!fp) {
		perror("fopen()");
		exit(1);
	}
	if (256 != fwrite(ether_a49, 1, 256, fp)) {
		perror("fwrite()");
		exit(1);
	}
	fclose(fp);
	return 0;
}