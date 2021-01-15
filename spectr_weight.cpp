#include "Header.h"

int main()
{
	short c;
	do
	{
		std::string path_to_read;
		std::string path_to_out;

		std::cout << "\nEnter path to file to read: "; std::cin >> path_to_read;

		std::ifstream in(path_to_read);
		linear_subspace obj(in);

		in.close();


		std::cout << "Enter path to file to output: "; std::cin >> path_to_out;

		std::fstream out(path_to_out);

		if (!out.is_open()) std::cout << "error";

		obj.spec_weight(out);

		out.close();

		std::cout << "\n\ndo you want to continue?(1 - yes/ 0 - no) "; std::cin >> c;
	}
	while (c != 0);


	return 0;
}