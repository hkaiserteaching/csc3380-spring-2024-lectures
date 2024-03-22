
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

// hold all information related to a single student
struct student_info
{
    std::string name;                // students name
    double midterm, final;           // midterm and final exam grades
    std::vector<double> homework;    // all homework grades
};

// read all information related to one student
std::istream& read_hw(std::istream& in, std::vector<double>& hw)
{
    if (in)
    {
        hw.clear();    // get rid of previous contents

        // read homework grades
        double x;
        while (in >> x)
            hw.push_back(x);

        // clear the stream so that input will work for
        // the next student
        in.clear();
    }
    return in;
}

std::istream& operator>>(std::istream& in, student_info& s)
{
    // read the students name, midterm and final exam grades
    in >> s.name >> s.midterm >> s.final;

    // read all homework grades for this student
    return read_hw(in, s.homework);
}

// compute the median of a std::vector<double>
// note: calling this function copies the whole std::vector
double median(std::vector<double> vec)
{
    auto size = vec.size();
    if (size == 0)
        throw std::domain_error("std::vector is empty, median undefined");

    std::sort(vec.begin(), vec.end());
    auto mid = size / 2;
    return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

// Calculate the final grade for one student
// compute a student's overall grade from midterm and final exam
// grades and homework grade
double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

// Compute a student's overall grade from midterm and
// final exam grades and all homework grades.
// This function does not copy the std::vector argument
// (as median does so for us).
double grade(double midterm, double final, std::vector<double> const& hw)
{
    if (hw.size() == 0)
        throw std::domain_error("student has done no homework");
    return grade(midterm, final, median(hw));
}

double grade(student_info const& s)
{
    return grade(s.midterm, s.final, s.homework);
}

bool did_all_homework(student_info const& s)
{
    return std::find(s.homework.begin(), s.homework.end(), 0) ==
        s.homework.end();
}

// Median calculation and analysis
double median_grade(student_info const& s)
{
    try
    {
        return grade(s);    // throws if no homework
    }
    catch (std::domain_error const&)
    {
        return grade(s.midterm, s.final, 0);
    }
}

double median_analysis(std::vector<student_info> const& students)
{
    std::vector<double> grades;
    std::transform(students.begin(), students.end(), std::back_inserter(grades),
        median_grade);
    return median(grades);
}

// Average calculation and analysis
double average(std::vector<double> const& v)
{
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double average_grade(student_info const& s)
{
    return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(std::vector<student_info> const& students)
{
    std::vector<double> grades;
    std::transform(students.begin(), students.end(), std::back_inserter(grades),
        average_grade);
    return median(grades);
}

// median of the nonzero elements of s.homework, or 0 if no such elements exist
double optimistic_median(student_info const& s)
{
    std::vector<double> nonzero;
    std::remove_copy(
        s.homework.begin(), s.homework.end(), std::back_inserter(nonzero), 0);

    if (nonzero.empty())
        return grade(s.midterm, s.final, 0);
    return grade(s.midterm, s.final, median(nonzero));
}

double optimistic_median_analysis(std::vector<student_info> const& students)
{
    std::vector<double> grades;
    std::transform(students.begin(), students.end(), std::back_inserter(grades),
        optimistic_median);
    return median(grades);
}

// generate output
void write_analysis(std::ostream& out, std::string const& name,
    double analysis(std::vector<student_info> const&),
    std::vector<student_info> const& did,
    std::vector<student_info> const& didnt)
{
    out << name << ": median(did) = " << analysis(did)
        << ", median(didnt) = " << analysis(didnt) << std::endl;
}

int main()
{
    std::ifstream in("student_grades.txt");

    // read and store all the records, find the length of
    // the longest name
    std::vector<student_info> students;    // all student records
    std::string::size_type maxlen = 0;     // length of longest name

    // read all the records, separating them based on
    // whether all homework was done
    std::vector<student_info> did, didnt;

    student_info student;
    while (in >> student)
    {
        if (did_all_homework(student))
            did.push_back(student);
        else
            didnt.push_back(student);
    }

    // check that both groups contain data
    if (did.empty())
        std::cout << "No student did all the homework!" << std::endl;
    if (didnt.empty())
        std::cout << "Every student did all the homework!" << std::endl;

    // sorting the student data using a lambda function
    std::sort(students.begin(), students.end(),
        [](student_info const& x, student_info const& y) {
            return x.name < y.name;
        });

    // do the analyses
    write_analysis(std::cout, "median", median_analysis, did, didnt);
    write_analysis(std::cout, "average", average_analysis, did, didnt);
    write_analysis(std::cout, "median of homework turned in",
        optimistic_median_analysis, did, didnt);

    return 0;
}
