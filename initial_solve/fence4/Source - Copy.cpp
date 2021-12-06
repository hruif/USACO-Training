/*
ID: ruifanl1
TASK: fence4
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <float.h>
#include <vector>

using namespace std;

struct Point {
	double x;
	double y;
	Point() {
		x = 1000000;
		y = 1000000;
	}
	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}
	void setCoords(double x, double y) {
		this->x = x;
		this->y = y;
	}
};

struct Lseg { // y = ax + b
	double rise; // x = rise / run
	double run;
	double b;
	Point e1; // endpoints
	Point e2;
	Lseg() {
		e1.setCoords(1000000, 1000000);
		e2.setCoords(1000000, 1000000);
	}
	Lseg(double rise, double run, double b, Point e1, Point e2) {
		this->rise = rise;
		this->run = run;
		this->b = b;
		this->e1 = e1;
		this->e2 = e2;
	}
	Lseg(double rise, double run, double b) {
		this->rise = rise;
		this->run = run;
		this->b = b;
		e1.setCoords(1000000, 1000000);
		e2.setCoords(1000000, 1000000);
	}
};

int N;
Point observer;
Point verts[200];
Lseg fences[200];

bool closeEnough(double a, double b) { // to account for possible inaccuracies with doubles
	if (a == b) {
		return true;
	}
	if (a < b) {
		double t = a;
		a = b;
		b = t;
	}
	double f = 0.000000000001;
	if (a - b < f) {
		return true;
	}
	return false;
}

Lseg makeLseg(Point& p1, Point& p2) {
	Point& left = p1.x < p2.x ? p1 : p2;
	Point& right = p1.x < p2.x ? p2 : p1;
	double rise = right.y - left.y;
	double run = right.x - left.x;
	double b = p1.y - (p1.x * (rise / run));
	return Lseg(rise, run, b, p1, p2);
}

bool inLseg(Lseg& f, Point& p) { // assuming point is on line, check if on line segment
	Point& a = f.e1;
	Point& b = f.e2;
	double top = max(a.y, b.y);
	double left = min(a.x, b.x);
	double bot = min(a.y, b.y);
	double right = max(a.x, b.x);
	bool x = (p.x >= left || closeEnough(p.x, left)) && (p.x <= right || closeEnough(p.x, right));
	bool y = (p.y >= bot || closeEnough(p.y, bot)) && (p.y <= top || closeEnough(p.y, top));
	return x && y;
}

bool inLsegStrict(Lseg& f, Point p) { // assuming point is on line, check if on line segment (not including endpoints)
	Point& a = f.e1;
	Point& b = f.e2;
	double top = max(a.y, b.y);
	double left = min(a.x, b.x);
	double bot = min(a.y, b.y);
	double right = max(a.x, b.x);

	if (f.rise == 0) {
		return p.x > left && p.x < right;
	}
	if (f.run == 0) {
		return p.y > bot && p.y < top;
	}

	bool isTop = p.y == top;
	bool isLeft = p.x == left;
	bool isBot = p.y == bot;
	bool isRight = p.x == right;
	bool vert = isTop || isBot;
	bool hor = isLeft || isRight;
	if (vert && hor) {
		return false;
	}

	return (p.x > left && p.x < right) && (p.y > bot && p.y < top);
}

Point findPotentialIntersect(Lseg& a, Lseg& b) {
	double c = a.b - b.b;
	double rise = (b.rise * a.run) - (a.rise * b.run);
	if (rise == 0) {
		if (c == 0 || closeEnough(c, 0)) {
			if (inLseg(a, b.e1)) {
				return b.e1;
			}
			if (inLseg(a, b.e2)) {
				return b.e2;
			}
			if (inLseg(b, a.e1)) {
				return a.e1;
			}
			if (inLseg(b, a.e2)) {
				return a.e2;
			}
		}
		return Point();
	}
	if (a.run == 0) {
		return Point(a.e1.x, (b.rise / b.run) * a.e1.x + b.b);
	}
	if (b.run == 0) {
		return Point(b.e1.x, (a.rise / a.run) * b.e1.x + a.b);
	}
	double run = a.run * b.run;
	double x = c / (rise / run);
	return Point(x, (a.rise / a.run) * x + a.b);
}

bool intersecting(Lseg&a, Lseg& b) {
	Point ip = findPotentialIntersect(a, b); // intersecting point

	bool inA = inLseg(a, ip);
	bool inB = inLseg(b, ip);

	return inA && inB;
}

bool validInput() {
	for (int i = 0; i < N; i++) {
		Lseg f = makeLseg(verts[i], verts[i < N - 1 ? i + 1 : 0]);
		for (int j = 0; j < i; j++) {
			Point ip = findPotentialIntersect(fences[j], f); // intersecting point

			bool inA = inLsegStrict(fences[j], ip);
			bool inB = inLsegStrict(f, ip);

			if (inA && inB) {
				return false;
			}
		}
		fences[i] = f;
	}
	Point t = fences[N - 1].e1;
	fences[N - 1].e1 = fences[N - 1].e2;
	fences[N - 1].e2 = t;
	return true;
}

bool checkVisibility(int fIndex) {
	vector<Lseg> fParts;
	fParts.push_back(fences[fIndex]);
	for (int i = 0; i < N; i++) {
		if (i == fIndex) {
			continue;
		}

		Lseg blocking = fences[i];
		Lseg ob_b1 = makeLseg(observer, blocking.e1);
		Lseg ob_b2 = makeLseg(observer, blocking.e2);

		for (int j = 0; j < fParts.size(); j++) {
			Lseg target = fParts[j];

			Lseg ob_t1 = makeLseg(observer, target.e1);
			Lseg ob_t2 = makeLseg(observer, target.e2);

			bool b_t1_intersect = intersecting(blocking, ob_t1);
			bool b_t2_intersect = intersecting(blocking, ob_t2);

			if (b_t1_intersect && b_t2_intersect) {
				fParts.erase(fParts.begin() + j--);
				continue;
			}

			Point potential_cut1 = findPotentialIntersect(target, ob_b1);
			Point potential_cut2 = findPotentialIntersect(target, ob_b2);

			if (b_t1_intersect || b_t2_intersect) {
				if (inLsegStrict(target, potential_cut1)) {
					fParts.push_back(makeLseg(potential_cut1, target.e1));
					fParts.push_back(makeLseg(potential_cut1, target.e2));
					fParts.erase(fParts.begin() + j--);
					continue;
				}

				if (inLsegStrict(target, potential_cut2)) {
					fParts.push_back(makeLseg(potential_cut2, target.e1));
					fParts.push_back(makeLseg(potential_cut2, target.e2));
					fParts.erase(fParts.begin() + j--);
					continue;
				}
				continue;
			}
			else {
				if (intersecting(target, ob_b1) || intersecting(target, ob_b2)) {
					continue;
				}

				if (inLsegStrict(target, potential_cut1) || inLsegStrict(target, potential_cut2)) {
					if (inLsegStrict(target, potential_cut1) && inLsegStrict(target, potential_cut2)) {
						if (target.rise == 0) {
							Point leftT = target.e1.x > target.e2.x ? target.e2 : target.e1;
							Point rightT = target.e1.x > target.e2.x ? target.e1 : target.e2;
							Point leftCut = potential_cut1.x > potential_cut2.x ? potential_cut2 : potential_cut1;
							Point rightCut = potential_cut1.x > potential_cut2.x ? potential_cut1 : potential_cut2;

							fParts.push_back(makeLseg(leftT, leftCut));
							fParts.push_back(makeLseg(rightT, rightCut));
							fParts.erase(fParts.begin() + j--);
							continue;
						}
						else {
							Point botT = target.e1.y > target.e2.y ? target.e2 : target.e1;
							Point topT = target.e1.y > target.e2.y ? target.e1 : target.e2;
							Point botCut = potential_cut1.y > potential_cut2.y ? potential_cut2 : potential_cut1;
							Point topCut = potential_cut1.y > potential_cut2.y ? potential_cut1 : potential_cut2;

							fParts.push_back(makeLseg(botT, botCut));
							fParts.push_back(makeLseg(topT, topCut));
							fParts.erase(fParts.begin() + j--);
							continue;
						}
					}
					else {
						cout << "huh\n";
					}
				}
			}
		}
	}
	if (fParts.size() > 0) {
		return true;
	}
	return false;
}

void sortOutput(int* visibles, int numOfVisibles) {
	if (visibles[numOfVisibles - 1] == N - 1 && visibles[numOfVisibles - 2] == N - 2) {
		visibles[numOfVisibles - 1] = N - 2;
		visibles[numOfVisibles - 2] = N - 1;
	}
}

int main() {
	ifstream fin("fence4.in");
	fin >> N;
	fin >> observer.x >> observer.y;
	for (int i = 0; i < N; i++) {
		int x, y;
		fin >> x >> y;
		verts[i].setCoords(x, y);
	}
	if (!validInput()) {
		ofstream fout("fence4.out");
		fout << "NOFENCE\n";
		return 0;
	}

	int numOfVisibles = 0;
	int visibles[200];
	for (int i = 0; i < N; i++) {
		if (checkVisibility(i)) {
			visibles[numOfVisibles++] = i;
		}
	}

	ofstream fout("fence4.out");
	sortOutput(visibles, numOfVisibles);
	fout << numOfVisibles << '\n';
	for (int i = 0; i < numOfVisibles; i++) {
		Lseg& f = fences[visibles[i]];
		fout << f.e1.x << ' ' << f.e1.y << ' ' << f.e2.x << ' ' << f.e2.y << '\n';
	}
}
