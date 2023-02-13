# include "stack.hpp"
# include <iostream>
# include <list>
# include <string>
typedef std::list<int> container_type;
#define t_stack_ ft::stack<int, container_type>
void	cmp(const t_stack_ &lhs, const t_stack_ &rhs) {
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}
int		main(void) {
	container_type	ctnr;
	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);
	t_stack_	stck(ctnr);
	t_stack_	stck2(ctnr);
	cmp(stck, stck);  // 0
	cmp(stck, stck2); // 1
	stck2.push(60);
	stck2.push(61);
	stck2.push(62);
	cmp(stck, stck2); // 2
	cmp(stck2, stck); // 3

	stck.push(42);

	cmp(stck, stck2); // 4
	cmp(stck2, stck); // 5

	stck.push(100);

	cmp(stck, stck2); // 6
	cmp(stck2, stck); // 7
	return (0);
}
