#include<cstdio>
class a
{
	public:
		template<typename T>
		void print(int i)
		{
			
		}
};

		template<>
		void a::print<float>(int i)
		{
			std::printf("%f\n", i);
		}
		template<>
		void a::print<int>(int i)
		{
			std::printf("%d\n", i);
		}
int main()
{
	a o;
	o.print<int>(3);
	o.print<float>(3);
	return 0;
}
