#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#define C const
#define AutoT template<typename T> auto 
#define AutoTU template<typename T,typename U> auto
#define KeyType int
#define ValVec vector<T>
#define KeyVec vector<KeyType>
#define Val(x) ValVec x
#define Key(x) KeyVec x
#define Sz(x) x.size()
#define Grow(x,y) x.reserve(Sz(y))
#define For(x,i) for(auto i=0; i<Sz(x); i++) 
#define ValLike(x,y) Val(x);Grow(x, y) 
#define Ins(x,y) x.push_back(y)
#define R(x) return x

auto assert(C bool cond,C char msg[]) { if(!cond){ cout << "ASSERT: " << msg << "\n"; exit(1); } R(cond); } // TEST
AutoT emit(C Val(x)) { cout<<"["; for(auto xx:x)cout<<xx<<" "; cout<<"]\n"; R(x); } // DEBUG
AutoT emit(C T x) { cout<<x<<"\n"; R(x); }
AutoT emit(T x,C char s[]) { cout << s << ": "; R(emit(x)); }
AutoT amend(Val(x),C Key(y), C Val(z)) { For(y, j){ x[y[j]]=z[j]; } R(x); }     // BASIC OPERATIONS 
AutoT amend(Val(x),C Key(y), auto f) { For(y, j){ x[y[j]]=f(x[y[j]]); } R(x); }     // BASIC OPERATIONS 
AutoT apply(C Val(x),C Key(y)) { R(x[y[Sz(y)-1]]); }
AutoT at(C Val(x),T y) { R(x[y]); } // Indexing
AutoT at(C Val(x),C Key(y)) { ValLike(r, y); For(y, j){Ins(r,x[y[j]]);} R(r); }
AutoT makec(T x) { R(vector<char>(x.begin(),x.end())); }
AutoT makei(T x) { R(vector<int>(x.begin(),x.end())); }
AutoT til(C T max) { Val(r); r.reserve(max); for(auto i=0;i<max;i++) Ins(r,i); R(r); }
AutoT each(C Val(x),auto f) { ValLike(r, x); For(x,i){ Ins(r,f(x[i])); } R(r); }
AutoT where(C Val(x),auto f) { KeyVec(r); For(x,i){ if(f(x[i])) { Ins(r,i); } } R(r); }
AutoT where(C Val(x),T y) { KeyVec(r); For(x,i){ if (x[i]==y) Ins(r,i); } R(r); }

int dub(int n) { return n * 2; }
int tests(void) {
	#define TESTN 50
	auto c=til(TESTN);
	assert(emit(c.size())==TESTN,"t-cs");
	assert(at(c, til(3))==til(3),"t-cf3");
	c=amend(c, vector<int>{0,1}, vector<int>{10,10});
	assert(c[0]==10 && c[1]==10,"t-amend0");
	assert(each(c, dub)[0]==20,"t-dub0");
	emit(c,"c before c2");
	auto c2=c;
	c2=amend(c2, vector<int>{0}, [](int x)->int{R(100);});
	emit(c2,"c2");
	assert(c2[0]==100,"c2-amend0");
	auto e=where(c,10);
	assert(e==vector<int>{0,1,10},"t-where10");
	auto f=where(c,[](int x)->bool{R(x==10);});
	assert(f==vector<int>{0,1,10},"t-wherefun10");

	auto g=vector<float>{0.1, 0.5, 0.9};
	g=amend(g, vector<int>{0}, vector<float>{2});
	assert(g[0]>1,"t-amendfloat");

	string s="hello";
	auto cs=makec(s);
	emit(cs,"cs");
	auto csw=where(cs,'h');
	emit(csw,"whereres");
	emit(1,"done");
}

int main(void) {
	if(!tests()) exit(0);
}

/* 
 TODO, notes..
 1. speed: push_back() vs size();x[i]=y
 2. override more default operators where it makes sense
 3. dont neglect high level and control verbs
 4. make()/cast()
 5. does cond() make sense?
*/
