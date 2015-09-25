from math import sqrt, pi, atan2

EPS = 1e-6
RAD = 180.0 / pi;

class Point:
	"""docstring for Point"""
	def __init__(self, x=0, y=0):
		self.x, self.y = x, y

	def __str__(self):
		return '{0} {1}'.format(self.x, self.y)

	len = lambda self: sqrt(self.x ** 2 + self.y ** 2)

	def normalize(self):
		try:
			return Point(self.x / self.len(), self.y / self.len())
		except:
			return Point()  # TODO

	def __cmp__(self, other):
		if not isinstance(other, Point): raise TypeError
		return 0 if (abs(self.x - other.x) < EPS and abs(self.y - other.y) < EPS) else (self.len() - other.len())

	def __pos__(self):
		return self

	def __neg__(self):
		return Point(-self.x, -self.y)

	def __abs__(self):
		return Point(abs(self.x), abs(self.y))

	def __add__(self, other):
		if not isinstance(other, Point): raise TypeError
		return Point(self.x + other.x, self.y + other.y)

	def __sub__(self, other):
		return self + (-other)

	def __mul__(self, other):
		if isinstance(other, Point):
			return self.x * other.x + self.y * other.y
		elif type(other) == int:
			return Point(self.x * other, self.y * other)
		raise TypeError

	def __rmul__(self, other):
		pass
		# return other * self TODO

	def __xor__(self, other):
		if not isinstance(other, Point): raise TypeError
		return self.x * other.y - self.y * other.x

	def __hash__(self):
		pass  # TODO

def angle(a, b):
	return abs(atan2(a ^ b, a * b));
	# return abs(atan2(a ^ b, a * b)) * RAD;

def len(a, b):
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));

class Line:
	"""docstring for Line"""
	def __init__(self, a, b, c):
		self.a = a
		self.b = b
		self.c = c

	def __init__(self, first=Point(), second=Point()):
		self.a = first.y - second.y
		self.b = second.x - first.x
		self.c = -self.a * first.x - self.b * first.y

	@staticmethod
	def gcd(a, b):
		return gcd(b, a % b) if b else a

	def normalize(self):
		if not type(self.a) == int and type(self.b) == int and type(self.c) == int: raise TypeError
		g = gcd(a, gcd(b, c))

		a = self.a / g
		b = self.b / g
		c = self.c / g

		if a < 0 or (a == 0 and b < 0):
			a *= -1
			b *= -1
			c *= -1

		return Line(a, b, c)

	def __cmp__(self, other):
		first = self.normalize()
		second = self.normalize()

		return 0 if (first.a == second.a and first.b == second.b and first.c == second.c) else 228  # TODO

	def __hash__(self):
		pass  # TODO

def intersection(f, s):
	x = (f.b * s.c - s.b * f.c) / (s.b * f.a - f.b * s.a)
	y = (f.a * s.c - s.a * f.c) / (s.a * f.b - f.a * s.b)
	return Point(x, y)

class Section(Line):
	"""docstring for Section"""
	def __init__(self, first=Point(), second=Point()):
		super().__init__(first, second)
		self.first = first
		self.second = second
		
def _intersect(a, b):
	if a.first.x > a.second.x: swap(a.first.x, a.second.x)
	if a.first.y > a.second.y: swap(a.first.y, a.second.y)
	if b.first.x > b.second.x: swap(b.first.x, b.second.x)
	if b.first.y > b.second.y: swap(b.first.y, b.second.y)
	return max(a.first.x, b.first.x) <= min(a.second.x, b.second.x) and max(a.first.y, b.first.y) <= min(a.second.y, b.second.y)

def intersect(a, b):
	return _intersect(a, b) and ((a.second - a.first) ^ (b.first - a.first)) * ((a.second - a.first) ^ (b.second - a.first)) <= 0 and ((b.second - b.first) ^ (a.first - b.first)) * ((b.second - b.first) ^ (a.second - b.first)) <= 0


# Я устал
