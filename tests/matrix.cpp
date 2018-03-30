#include <cassert>
#include <catch.hpp>
#include <sstream>

#include "matrix.hpp"

TEST_CASE("creating matrix")
{
    matrix_t<int>  matrix;
    REQUIRE( matrix.rows() == 0 );
    REQUIRE( matrix.collumns() == 0 );
}

TEST_CASE("reading matrix")
{
    std::string input{
        "3, 3\n"
        "1 1 1\n"
        "2 2 2\n"
        "3 3 3" };
    matrix_t<int>  matrix;
    std::istringstream istream{ input };
    
    REQUIRE( matrix.read( istream ) );
    REQUIRE( matrix.rows() == 3 );
    REQUIRE( matrix.collumns() == 3 );
    
    std::ostringstream ostream;
    matrix.write( ostream );
    
    REQUIRE( input == ostream.str() );
}
//template <typename Type>//шаблонная ф-я
matrix_t<int> matrix( std::string const & representation )
{
    matrix_t<int> result;
    
    std::istringstream istream{ representation };
    assert( result.read( istream ) );
    
    return result;
}
//template <typename Type>
std::string representation( matrix_t<int> const & matrix )
{
    std::ostringstream ostream;
    matrix.write( ostream );
    
    return ostream.str();
}

TEST_CASE("addings matrixs")
{
    std::string first_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    std::string second_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    matrix_t<int> first_matrix = matrix( first_matrix_representation );
    matrix_t<int> second_matrix = matrix( second_matrix_representation );
    
    matrix_t<int> result_matrix = first_matrix + second_matrix;

    std::string expected_result_matrix_representation{
        "1, 3\n"
        "2 2 2\n"
    };
    
    REQUIRE( representation( result_matrix ) == expected_result_matrix_representation );
}

TEST_CASE("subtracting matrixs")
{
    std::string first_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    std::string second_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    matrix_t<int> first_matrix = matrix( first_matrix_representation );
    matrix_t<int> second_matrix = matrix( second_matrix_representation );
    
    matrix_t<int> result_matrix = first_matrix - second_matrix;

    std::string expected_result_matrix_representation{
        "1, 3\n"
        "0 0 0\n"
    };
    
    REQUIRE( representation( result_matrix ) == expected_result_matrix_representation );
}

TEST_CASE("multiplying matrixs")
{
    std::string first_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    std::string second_matrix_representation{
        "3, 1\n"
        "1\n"
        "1\n"
        "1\n"
    };
    matrix_t<int> first_matrix = matrix( first_matrix_representation );
    matrix_t<int> second_matrix = matrix( second_matrix_representation );
    
    matrix_t<int> result_matrix = first_matrix * second_matrix;

    std::string expected_result_matrix_representation{
        "1, 1\n"
        "3"
    };
    
    REQUIRE( representation( result_matrix ) == expected_result_matrix_representation );
}

TEST_CASE("addings_2 matrixs")
{
    std::string first_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    std::string second_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    matrix_t<int> first_matrix = matrix( first_matrix_representation );
    matrix_t<int> second_matrix = matrix( second_matrix_representation );
    
    first_matrix += second_matrix;

    std::string expected_result_matrix_representation{
        "1, 3\n"
        "2 2 2\n"
    };
    
    REQUIRE( representation( first_matrix ) == expected_result_matrix_representation );
}

TEST_CASE("subtracting_2 matrixs")
{
    std::string first_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    std::string second_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    matrix_t<int> first_matrix = matrix( first_matrix_representation );
    matrix_t<int> second_matrix = matrix( second_matrix_representation );
    
    first_matrix -= second_matrix;

    std::string expected_result_matrix_representation{
        "1, 3\n"
        "0 0 0\n"
    };
    
    REQUIRE( representation( first_matrix ) == expected_result_matrix_representation );
}

TEST_CASE("multiplying_2 matrixs")
{
    std::string first_matrix_representation{
        "1, 3\n"
        "1 1 1\n"
    };
    std::string second_matrix_representation{
        "3, 1\n"
        "1\n"
        "1\n"
        "1\n"
    };
    matrix_t<int> first_matrix = matrix( first_matrix_representation );
    matrix_t<int> second_matrix = matrix( second_matrix_representation );
    
    first_matrix *= second_matrix;

    std::string expected_result_matrix_representation{
        "1, 1\n"
        "3"
    };
    
    REQUIRE( representation( first_matrix ) == expected_result_matrix_representation );
}

TEST_CASE("addings matrixs 3x1")
{
    std::string first_matrix_representation{
        "3, 1\n"
        "1\n"
        "1\n"
        "1\n"
    };
    std::string second_matrix_representation{
        "3, 1\n"
        "1\n"
        "1\n"
        "1\n"
    };
    matrix_t<int> first_matrix = matrix( first_matrix_representation );
    matrix_t<int> second_matrix = matrix( second_matrix_representation );
    
    matrix_t<int> result_matrix = first_matrix + second_matrix;

    std::string expected_result_matrix_representation{
        "3, 1\n"
        "2\n"
        "2\n"
        "2\n"
    };
    
    REQUIRE( representation( result_matrix ) == expected_result_matrix_representation );
}
