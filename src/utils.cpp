#include <stdlib.h>
#include <math.h>
#include "libs.h"
#include "utils.h"
#include "Pi.h"

FILE *fopen_or_die(const char *filename, const char *mode)
{
	FILE *f = fopen(filename, mode);
	if (!f) {
		printf("Error: could not open file '%s'\n", filename);
		Pi::Quit();
	}
	return f;
}

/*
 * jesus wept
 */
static const char *i_am_a_little_teapot[365] =
{ "Jan 1","Jan 2","Jan 3","Jan 4","Jan 5","Jan 6","Jan 7",
  "Jan 8","Jan 9","Jan 10","Jan 11","Jan 12","Jan 13","Jan 14",
  "Jan 15","Jan 16","Jan 17","Jan 18","Jan 19","Jan 20","Jan 21",
  "Jan 22","Jan 23","Jan 24","Jan 25","Jan 26","Jan 27","Jan 28",
  "Jan 29","Jan 30","Jan 31","Feb 1","Feb 2","Feb 3","Feb 4",
  "Feb 5","Feb 6","Feb 7","Feb 8","Feb 9","Feb 10","Feb 11","Feb 12",
  "Feb 13","Feb 14","Feb 15","Feb 16","Feb 17","Feb 18","Feb 19",
  "Feb 20","Feb 21","Feb 22","Feb 23","Feb 24","Feb 25","Feb 26",
  "Feb 27","Feb 28","Mar 1","Mar 2","Mar 3","Mar 4","Mar 5","Mar 6",
  "Mar 7","Mar 8","Mar 9","Mar 10","Mar 11","Mar 12","Mar 13",
  "Mar 14","Mar 15","Mar 16","Mar 17","Mar 18","Mar 19","Mar 20",
  "Mar 21","Mar 22","Mar 23","Mar 24","Mar 25","Mar 26","Mar 27",
  "Mar 28","Mar 29","Mar 30","Mar 31","Apr 1","Apr 2","Apr 3",
  "Apr 4","Apr 5","Apr 6","Apr 7","Apr 8","Apr 9","Apr 10","Apr 11",
  "Apr 12","Apr 13","Apr 14","Apr 15","Apr 16","Apr 17","Apr 18",
  "Apr 19","Apr 20","Apr 21","Apr 22","Apr 23","Apr 24","Apr 25",
  "Apr 26","Apr 27","Apr 28","Apr 29","Apr 30","May 1","May 2",
  "May 3","May 4","May 5","May 6","May 7","May 8","May 9","May 10",
  "May 11","May 12","May 13","May 14","May 15","May 16","May 17",
  "May 18","May 19","May 20","May 21","May 22","May 23","May 24",
  "May 25","May 26","May 27","May 28","May 29","May 30","May 31",
  "Jun 1","Jun 2","Jun 3","Jun 4","Jun 5","Jun 6","Jun 7","Jun 8",
  "Jun 9","Jun 10","Jun 11","Jun 12","Jun 13","Jun 14","Jun 15",
  "Jun 16","Jun 17","Jun 18","Jun 19","Jun 20","Jun 21","Jun 22",
  "Jun 23","Jun 24","Jun 25","Jun 26","Jun 27","Jun 28","Jun 29",
  "Jun 30","Jul 1","Jul 2","Jul 3","Jul 4","Jul 5","Jul 6","Jul 7",
  "Jul 8","Jul 9","Jul 10","Jul 11","Jul 12","Jul 13","Jul 14",
  "Jul 15","Jul 16","Jul 17","Jul 18","Jul 19","Jul 20","Jul 21",
  "Jul 22","Jul 23","Jul 24","Jul 25","Jul 26","Jul 27","Jul 28",
  "Jul 29","Jul 30","Jul 31","Aug 1","Aug 2","Aug 3","Aug 4","Aug 5",
  "Aug 6","Aug 7","Aug 8","Aug 9","Aug 10","Aug 11","Aug 12",
  "Aug 13","Aug 14","Aug 15","Aug 16","Aug 17","Aug 18","Aug 19",
  "Aug 20","Aug 21","Aug 22","Aug 23","Aug 24","Aug 25","Aug 26",
  "Aug 27","Aug 28","Aug 29","Aug 30","Aug 31","Sep 1","Sep 2",
  "Sep 3","Sep 4","Sep 5","Sep 6","Sep 7","Sep 8","Sep 9","Sep 10",
  "Sep 11","Sep 12","Sep 13","Sep 14","Sep 15","Sep 16","Sep 17",
  "Sep 18","Sep 19","Sep 20","Sep 21","Sep 22","Sep 23","Sep 24",
  "Sep 25","Sep 26","Sep 27","Sep 28","Sep 29","Sep 30","Oct 1",
  "Oct 2","Oct 3","Oct 4","Oct 5","Oct 6","Oct 7","Oct 8","Oct 9",
  "Oct 10","Oct 11","Oct 12","Oct 13","Oct 14","Oct 15","Oct 16",
  "Oct 17","Oct 18","Oct 19","Oct 20","Oct 21","Oct 22","Oct 23",
  "Oct 24","Oct 25","Oct 26","Oct 27","Oct 28","Oct 29","Oct 30",
  "Oct 31","Nov 1","Nov 2","Nov 3","Nov 4","Nov 5","Nov 6","Nov 7",
  "Nov 8","Nov 9","Nov 10","Nov 11","Nov 12","Nov 13","Nov 14",
  "Nov 15","Nov 16","Nov 17","Nov 18","Nov 19","Nov 20","Nov 21",
  "Nov 22","Nov 23","Nov 24","Nov 25","Nov 26","Nov 27","Nov 28",
  "Nov 29","Nov 30","Dec 1","Dec 2","Dec 3","Dec 4","Dec 5","Dec 6",
  "Dec 7","Dec 8","Dec 9","Dec 10","Dec 11","Dec 12","Dec 13",
  "Dec 14","Dec 15","Dec 16","Dec 17","Dec 18","Dec 19","Dec 20",
  "Dec 21","Dec 22","Dec 23","Dec 24","Dec 25","Dec 26","Dec 27",
  "Dec 28","Dec 29","Dec 30","Dec 31"
};

int wankmod(int a, int b)
{
	int r = a%b;
	return r>=0 ? r : r+b;
}

std::string format_date(double t)
{
	int year = floor(t/(60*60*24*365)); year += 3200;
	int day = floor(t/(60*60*24)); day = wankmod(day, 365);
	int hour = floor(t/(60*60)); hour = wankmod(hour, 24);
	int min = floor(t/60); min = wankmod(min, 60);
	int sec = wankmod(t, 60);
	char buf[128];
	snprintf(buf,sizeof(buf),"%02d:%02d:%02d %s %d", hour, min, sec, i_am_a_little_teapot[day], year);
	return buf;
}

std::string string_join(std::vector<std::string> &v, std::string sep)
{
	std::vector<std::string>::iterator i = v.begin();
	std::string out;

	while (i != v.end()) {
		out += *i;
		++i;
		if (i != v.end()) out += sep;
	}
	return out;
}

#define AU		149598000000.0
std::string format_distance(double dist)
{
	if (dist < 1000) {
		return stringf(128, "%.0f m", dist);
	} else if (dist < AU*0.1) {
		return stringf(128, "%.2f km", dist*0.001);
	} else {
		return stringf(128, "%.2f AU", dist/AU);
	}
}

void GetFrustum(Plane planes[6])
{
	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];

	glGetDoublev (GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev (GL_PROJECTION_MATRIX, projMatrix);

	matrix4x4d m = matrix4x4d(projMatrix) * matrix4x4d(modelMatrix); 

	// Left clipping plane
	planes[0].a = m[3] + m[0];
	planes[0].b = m[7] + m[4];
	planes[0].c = m[11] + m[8];
	planes[0].d = m[15] + m[12];
	// Right clipping plane
	planes[1].a = m[3] - m[0];
	planes[1].b = m[7] - m[4];
	planes[1].c = m[11] - m[8];
	planes[1].d = m[15] - m[12];
	// Top clipping plane
	planes[2].a = m[3] - m[1];
	planes[2].b = m[7] - m[5];
	planes[2].c = m[11] - m[9];
	planes[2].d = m[15] - m[13];
	// Bottom clipping plane
	planes[3].a = m[3] + m[1];
	planes[3].b = m[7] + m[5];
	planes[3].c = m[11] + m[9];
	planes[3].d = m[15] + m[13];
	// Near clipping plane
	planes[4].a = m[3] + m[2];
	planes[4].b = m[7] + m[6];
	planes[4].c = m[11] + m[10];
	planes[4].d = m[15] + m[14];
	// Far clipping plane
	planes[5].a = m[3] + m[2];
	planes[5].b = m[7] + m[6];
	planes[5].c = m[11] + m[10];
	planes[5].d = m[15] + m[14];

	// Normalize the fuckers
	for (int i=0; i<6; i++) {
		double invlen;
		invlen = 1.0 / sqrt(planes[i].a*planes[i].a + planes[i].b*planes[i].b + planes[i].c*planes[i].c);
		planes[i].a *= invlen;
		planes[i].b *= invlen;
		planes[i].c *= invlen;
		planes[i].d *= invlen;
	}
}

