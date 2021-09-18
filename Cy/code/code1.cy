// example cy app:
// filename: main.cy

AClass:
	int a
	int8 b
	float64 c

	AClass(int a, int8 b, float64 c)
		this.a = a
		this.b = b
		this.c = c


int Main(String args) #0
	AClass aclass = AClass(1, 2, 3.14)
	return 0
