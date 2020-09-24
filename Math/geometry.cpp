const double PI = acos(-1);

struct Point{
	double x, y;

	bool operator < (const Point &b) const {
		return tie(x,y) < tie(b.x,b.y);
		//return atan2(y,x) < atan2(b.y,b.x);
	}
	Point operator + (const Point &b) const {
		return {x+b.x,y+b.y};
	}
	Point operator - (const Point &b) const {
		return {x-b.x,y-b.y};
	}
	Point operator * (const double d) const {
		return {x*d,y*d};	
	}
	Point operator / (const double d) const {
		return {x/d,y/d};	
	}
	double operator * (const Point &b) const {
		return x*b.x + y*b.y;
	}
	double operator % (const Point &b) const { // Cross!
		return x*b.y - y*b.x;
	}
	Point(double xx, double yy): x(xx), y(yy){  } 
};

double Length( const Point &p ){
	return sqrt( p.x*p.x + p.y*p.y );
}  

int ori(const Point &a, const Point &b, const Point &c){
	int tmp = (c-a)%(b-a);
	if (tmp==0) return 0; //Collinear
	return tmp>0? 1: -1;
}

bool collinear(const Point &a, const Point &b, const Point &c){
	return ori(a, b, c)==0; 
}

bool btw(const Point &a, const Point &b, const Point &c){
	return(a-c)*(b-c)<=0; 
}

typedef Point Vector;

double Angle( const Vector &a, const Vector &b ){
	double A = Length(a);
	double B = Length(b);
	double v = a*b;
	double theta = acos( v/A/B );  
	return theta;
}

Vector rot(Vector vec, double a){
	return Vector(cos(a)*vec.x-sin(a)*vec.y, sin(a)*vec.x+cos(a)*vec.y);
}

Vector Normal(const Vector &v){
	return v / Length(v);
}

Point intersect_at(const Point &p, const Vector &v, const Point &q, const Vector &w){
	Vector u = q-p;
	return p+v*(u%w)/(q%w);
}

bool cmp(const Point&a, const Point &b){
	return a<b; 
	//Sort by x first, then by y. 
}

vector<Point> convex_hull(vector<Point>arr){
	sort (arr.begin(), arr.end(), cmp);
	vector<Point> p;
	int m = 0; // size of p
	for (int i=0; i<arr.size(); i++){ // Lower hull
		//cout<<"On the "<<i<<"-th one. "<<arr[i].x<<' '<<arr[i].y<<'\n';
		while (m>=2&&(p[m-1]-p[m-2])%(arr[i]-p[m-2])<0){
			//Get rid of a previous point 
			//cout<<"Got rid of "<<p[m-1].x<<' '<<p[m-1].y<<'\n';
			p.pop_back(); m--;
		}
		p.push_back(arr[i]); m++;
	}
	//cout<<"Onto upper hull"<<'\n';
	int tmp = m+1; //the size of lower hull +1
	for (int i=arr.size()-2; i>=0; i--){
		//cout<<"On the "<<i<<"-th one. "<<arr[i].x<<' '<<arr[i].y<<'\n';
		while (m>=tmp&&(p[m-1]-p[m-2])%(arr[i]-p[m-2])<0){
			//cout<<"Got rid of "<<p[m-1].x<<' '<<p[m-1].y<<'\n';
			p.pop_back(); m--;
		}
		p.push_back(arr[i]); m++;
	}
	//cout<<m<<'\n';
	if (arr.size()>1) p.pop_back(); //Repeated
	return p;
}

//Segment banana 

double signedArea(Point p[], int n){
	double re = 0.0;
	for (int i=0; i<n; i++){
		re+=p[i]%p[(i+1)%n];
	}
	return re/2.0; //Cross returns twice the triangle's area
}

bool intersect(const Point a, const Point b, const Point c, const Point d){
	int abc = ori(a, b, c);
	int abd = ori(a, b, d);
	int cda = ori(c, d, a);
	int cdb = ori(c, d, b);
	if (abc==0&&abd==0){
		return btw(a,b,c)||btw(a,b,d)||btw(c,d,a)||btw(c,d,b);
	}else return (abc*abd<=0&&cda*cdb<=0);
}
