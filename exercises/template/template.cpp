#include <typeinfo>
#include <iostream>
using namespace std;

template <typename ID_TYPE, typename NAME_TYPE, typename SCORE_TYPE>
class student {
	private:
		ID_TYPE stu_id;
		NAME_TYPE stu_name;  
		SCORE_TYPE stu_score; 
	public:
		student (ID_TYPE sid, NAME_TYPE sname, SCORE_TYPE sscore) {
			stu_id = sid;
			stu_name = sname;  
			stu_score = sscore; 
		}
		void print_length_of_name();
		void print_student_info();
		bool passed_the_subject(int lowest_mark_to_pass);
};

/* The defintion of the print_dataType_info() function */
template <typename ID_TYPE, typename NAME_TYPE, typename SCORE_TYPE>
void student<ID_TYPE, NAME_TYPE, SCORE_TYPE>::print_length_of_name() {
	cout << stu_name.length() << endl;
}

/* The defintion of the print_student_info() function */
template <typename ID_TYPE, typename NAME_TYPE, typename SCORE_TYPE>
void student<ID_TYPE, NAME_TYPE, SCORE_TYPE>::print_student_info() {
	cout << stu_id << " " << stu_name << " " << stu_score << endl;
}

/* The defintion of the print_student_info() function */
template <typename ID_TYPE, typename NAME_TYPE, typename SCORE_TYPE>
bool student<ID_TYPE, NAME_TYPE, SCORE_TYPE>::passed_the_subject(int lowest_mark_to_pass) {
	return stu_score >= lowest_mark_to_pass;
}

int main() {
	student <string, string, int> myobject1 ("001", "Jack", 35);
	myobject1.print_length_of_name();
	myobject1.print_student_info();
	cout << "Has student passed the subject? " << myobject1.passed_the_subject(50) << endl;

	cout << endl;

	student <int, string, double> myobject2 (1, "Tom", 70.0);
	myobject2.print_length_of_name();
	myobject2.print_student_info();
	cout << "Has student passed the subject? " << myobject2.passed_the_subject(50) << endl;
}