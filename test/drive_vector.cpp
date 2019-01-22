/*!
 * Test driver for the vector class.
 */
#include <iostream>
#include <sstream>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
#include <iterator>

#include "../include/vector.h"

/// Testing copy constructor.
template < typename T = int >
sc::vector<T> createVec( const sc::vector<T> & _v )
{
    sc::vector<T> temp( _v );
    return _v;
}

int main ( void )
{
    auto n_unit{0};

    // Unit #1: default constructor
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": default constructor.\n";
        sc::vector<int> vec;
        assert( vec.size() == 0 );
        assert( vec.capacity() == 0 );
        assert( vec.empty() == true );
        std::cout << ">>> Passed!\n\n";
    }

    // Unit #2: constructor (size)
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": constructor(size).\n";
        sc::vector<int> vec(10);
        assert( vec.size() == 0 );
        assert( vec.capacity() == 10 );
        assert( vec.empty() == true );
        std::cout << ">>> Passed!\n\n";
    }

    // Unit #3: initializer list constructor
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": initializer list constructor.\n";
        sc::vector<int> vec{ 1, 2, 3, 4, 5 };
        assert( vec.size() == 5 );
        assert( vec.empty() == false );

        // recover elements to test.
        auto i{0u};
        for ( auto it = vec.cbegin() ; it != vec.cend() ; ++it, ++i )
            assert( *it == i+1 );

        std::cout << ">>> Passed!\n\n";
    }

    // Unit #5: range constructor
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": range constructor.\n";
        sc::vector<int> vec{ 1, 2, 3, 4, 5 };
        sc::vector<int> vec2( vec.begin(), vec.end() );
        assert( vec2.size() == 5 );
        assert( vec2.empty() == false );

        // recover elements to test.
        auto i{1};
        for( auto e : vec2 )
            assert ( e == i++ );

        // Copy only part of the original range.
        sc::vector<int> vec3( std::next( vec.begin(), 1 ), std::next( vec.begin(), 3 ) );
        auto it2 = std::next( vec.begin(), 1 );
        for ( auto it = vec3.cbegin() ; it != vec3.cend() ; ++it, ++it2 )
            assert( *it == *it2 );

        std::cout << ">>> Passed!\n\n";
    }

    // Unit: copy constructor
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": copy constructor.\n";
        sc::vector<int> vec{ 1, 2, 3, 4, 5 };
        sc::vector<int> vec2( vec );
        assert( vec2.size() == 5 );
        assert( vec2.empty() == false );

        // recover elements to test.
        auto i{1};
        for( auto e : vec2 )
            assert ( e == i++ );

        // Changing vec (the original)...
        auto it = std::next( vec.begin(), 2 );
        *it = 10;
        // ... should not alter the copy.
        i = 1;
        for( auto e : vec2 )
            assert ( e == i++ );

        std::cout << ">>> Passed!\n\n";
    }

    // Unit: move constructor
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": move constructor.\n";
        sc::vector<int> vec{ 1, 2, 3, 4, 5 };
        sc::vector<int> vec2( std::move( vec ) );
        assert( vec2.size() == 5 );
        assert( vec2.empty() == false );

        // recover elements to test.
        auto i{1};
        for( auto e : vec2 )
            assert ( e == i++ );

        std::cout << ">>> Passed!\n\n";
    }

    // Unit: Assign operator.
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": assign operator.\n";
        sc::vector<int> vec{ 1, 2, 3, 4, 5 };
        sc::vector<int> vec2;

        vec2 = vec;
        assert( vec2.size() == 5 );
        assert( vec2.empty() == false );

        // recover elements to test.
        auto i{1};
        for( auto e : vec2 )
            assert ( e == i++ );

        std::cout << ">>> Passed!\n\n";
    }

    // Unit: Move assign operator.
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": move assign operator.\n";
        sc::vector<int> vec{ 1, 2, 3, 4, 5 };
        sc::vector<int> vec2;

        vec2 = std::move( vec );
        assert( vec2.size() == 5 );
        assert( vec2.empty() == false );
        assert( vec.size() == 0 );
        assert( vec.capacity() == 0 );
        assert( vec.empty() == true );

        // recover elements to test.
        auto i{1};
        for( auto e : vec2 )
            assert ( e == i++ );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": initializer list assignment.\n";
        sc::vector<int> vec = { 1, 2, 3, 4, 5 };

        assert( vec.size() == 5 );
        assert( vec.empty() == false );
        assert( vec.capacity() == 5 );

        // recover elements to test.
        auto i{1};
        for( auto e : vec )
            assert ( e == i++ );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": clear().\n";
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        assert( vec.size() == 5 );
        assert( vec.empty() == false );
        assert( vec.capacity() == 5 );

        vec.clear();
        assert( vec.size() == 0 );
        assert( vec.empty() == true );
        assert( vec.capacity() == 5 );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": push_front().\n";

        // #1 From an empty vector.
        sc::vector<int> vec;

        assert( vec.empty() == true );
        for ( auto i{0} ; i < 5 ; ++i )
        {
            vec.push_front( i+1 );
            assert( vec.size() == i+1 );
        }
        assert( vec.empty() == false );

        auto i{5};
        for ( const auto & e: vec )
            assert( e == i-- );

        vec.clear();
        assert( vec.empty() == true );
        for ( auto i{0} ; i < 5 ; ++i )
        {
            vec.push_front( i+1 );
            assert( vec.size() == i+1 );
        }
        assert( vec.empty() == false );
        i = 5;
        for ( const auto & e: vec )
            assert( e == i-- );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": push_back().\n";

        // #1 From an empty vector.
        sc::vector<int> vec;

        assert( vec.empty() == true );
        for ( auto i{0} ; i < 5 ; ++i )
        {
            vec.push_back( i+1 );
            assert( vec.size() == i+1 );
        }
        assert( vec.empty() == false );

        auto i{0};
        for ( const auto & e: vec )
            assert( e == ++i );

        vec.clear();
        assert( vec.empty() == true );
        for ( auto i{0} ; i < 5 ; ++i )
        {
            vec.push_back( i+1 );
            assert( vec.size() == i+1 );
        }
        assert( vec.empty() == false );
        i = 0;
        for ( const auto & e: vec )
            assert( e == ++i );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": pop_back().\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        while( not vec.empty() )
        {
            vec.pop_back();
            // Checke whether we have the same list except for the last.
            auto i {0};
            for ( const auto & e: vec )
                assert( e == ++i );
        }

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": pop_front().\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        auto start{1};
        while( not vec.empty() )
        {
            vec.pop_front();
            // Check whether we have the same list except for the first.
            auto i {start};
            for ( const auto & e: vec )
                assert( e == ++i );

            start++;
        }

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": front().\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        auto i{0};
        while( not vec.empty() )
        {
            assert( vec.front() == ++i );
            vec.pop_front();
        }

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": back().\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        auto i{5};
        while( not vec.empty() )
        {   
            assert( vec.back() == i-- );
            vec.pop_back();
        }

        std::cout << ">>> Passed!\n\n";
    }

    /*
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": assign(value).\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        vec.assign( -3 );
        assert( vec.size() == 5 );

        for ( const auto & e : vec )
            assert( e == -3 );

        std::cout << ">>> Passed!\n\n";
    }
    */

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": const operator[].\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        auto i{0};
        for ( const auto & e : vec )
            assert( e == vec[i++] );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": operator[].\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        for ( auto i{0} ; i < vec.size() ; ++i )
            vec[i] = 2*(i+1);

        auto i{0};
        for ( const auto & e : vec )
            assert( e == 2 * ++i );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": const at().\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        auto i{0};
        for ( const auto & e : vec )
            assert( e == vec.at(i++) );

        bool worked{ false };
        try { vec.at( vec.size() ); }
        catch ( const std::out_of_range & e )
        {
            worked = true;
        }
        assert( worked );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": at().\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        for ( auto i{0} ; i < vec.size() ; ++i )
            vec.at(i) = 2*(i+1);

        auto i{0};
        for ( const auto & e : vec )
            assert( e == 2 * ++i );

        bool worked{ false };
        try { vec.at( vec.size() ); }
        catch ( const std::out_of_range & e )
        {
            worked = true;
        }
        assert( worked );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": reserve().\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        assert( vec.capacity() == 5 );
        vec.reserve(10);
        assert( vec.capacity() == 10 );
        vec.reserve(3); // Nothing happens here.
        assert( vec.capacity() == 10 );

        auto i{0};
        for( const auto & e : vec )
            assert( e == ++i );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": shrink_to_fit().\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        assert( vec.capacity() == 5 );
        vec.pop_back();
        vec.pop_back();
        assert( vec.capacity() == 5 );
        vec.shrink_to_fit();
        assert( vec.capacity() == 3 );
        auto i{0};
        for( const auto & e : vec )
            assert( e == ++i );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": operator==().\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };
        sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
        sc::vector<int> vec3 { 1, 2, 8, 4, 5 };
        sc::vector<int> vec4 { 8, 4, 5 };

        assert( vec == vec2 );
        assert( not ( vec == vec3 ) );
        assert( not ( vec == vec4 ) );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": operator!=().\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };
        sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
        sc::vector<int> vec3 { 1, 2, 8, 4, 5 };
        sc::vector<int> vec4 { 8, 4, 5 };

        assert( not( vec != vec2 ) );
        assert( vec != vec3 );
        assert( vec != vec4 );
        assert( vec != (sc::vector<int>{ 1, 2, 3 } ) );

        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": insert(pos, value).\n";

        // #1 From an empty vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        vec.insert( vec.begin(), 0 );
    
        assert( vec == ( sc::vector<int>{ 0, 1, 2, 3, 4, 5 } ) );



        std::cout << ">>> Passed!\n\n";
    }

    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": insert(pos, first, last).\n";

        // Aux arrays.
        sc::vector<int> vec1 { 1, 2, 3, 4, 5 };
        sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
        sc::vector<int> source { 6, 7, 8, 9, 10 };

        // Inset at the begining.
        vec1.insert( vec1.begin(), source.begin(), source.end() );
        assert( vec1 == ( sc::vector<int>{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 } ) );

        // In the middle
        vec1 = vec2;
        vec1.insert( std::next( vec1.begin(), 2 ), source.begin(), source.end() );
        assert( vec1 == ( sc::vector<int>{ 1, 2, 6, 7, 8, 9, 10, 3, 4, 5 } ) );

        // At the end
        vec1 = vec2;
        vec1.insert( vec1.end(), source.begin(), source.end() );
        assert( vec1 == ( sc::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ) );

        // Outside
        vec1 = vec2;
        vec1.insert( std::next( vec1.end(), 2 ) , source.begin(), source.end() );
        assert( vec1 == ( sc::vector<int>{ 1, 2, 3, 4, 5 } ) );

        std::cout << ">>> Passed!\n\n";
    }
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": insert(pos, initializer_list).\n";

        // Aux arrays.
        sc::vector<int> vec1 { 1, 2, 3, 4, 5 };
        sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
        sc::vector<int> source { 6, 7, 8, 9, 10 };

        // Inset at the begining.
        vec1.insert( vec1.begin(), { 6, 7, 8, 9, 10 } );
        assert( vec1 == ( sc::vector<int>{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 } ) );

        // In the middle
        vec1 = vec2;
        vec1.insert( std::next( vec1.begin(), 2 ), { 6, 7, 8, 9, 10 } );
        assert( vec1 == ( sc::vector<int>{ 1, 2, 6, 7, 8, 9, 10, 3, 4, 5 } ) );

        // At the end
        vec1 = vec2;
        vec1.insert( vec1.end(), { 6, 7, 8, 9, 10 } );
        assert( vec1 == ( sc::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ) );

        // Outside
        vec1 = vec2;
        vec1.insert( std::next( vec1.end(), 2 ) , { 6, 7, 8, 9, 10 } );
        assert( vec1 == ( sc::vector<int>{ 1, 2, 3, 4, 5 } ) );

        std::cout << ">>> Passed!\n\n";
    }
//#ifdef IGNORE_THIS
// This method has the same signature as the assign( InItr, InItr ) of InItr is an integral type.
// So, we must block this for a while (until C++11).
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": assign(count, value).\n";

        // Initial vector.
        sc::vector<char> vec { 'a', 'b', 'c', 'd', 'e' };

        // assigning count values to sc::vector, with count < size().
        vec.assign( 3, 'x' );

        assert( vec == ( sc::vector<char>{ 'x', 'x', 'x' } ) );
        assert( vec.size() == 3 );
        assert( vec.capacity() == 3 );

        // assigning count values to sc::vector, with count == size().
        vec = { 'a', 'b', 'c', 'd', 'e' };
        vec.assign( 5, 'y' );
        assert( vec == ( sc::vector<char>{ 'y','y','y','y','y' } ) );
        assert( vec.size() == 5 );
        assert( vec.capacity() == 5 );

        // assigning count values to sc::vector, with count > size().
        vec = { 'a', 'b', 'c', 'd', 'e' };
        vec.assign( 8, 'z' );
        assert( vec == ( sc::vector<char>{ 'z','z','z','z','z','z','z','z' } ) );
        assert( vec.size() == 8 );
        assert( vec.capacity() == 8 );

        std::cout << ">>> Passed!\n\n";
    }
//#endif
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": erase(first, last) and erase(pos).\n";

        // Initial vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        // removing a segment from the beginning.
        auto past_last = vec.erase( vec.begin(), std::next(vec.begin(),3) );
        assert( vec.begin() == past_last );
        assert( vec == ( sc::vector<int>{ 4, 5 } ) );
        assert( vec.size() == 2 );

        // removing at the middle.
        vec = { 1, 2, 3, 4, 5 };
        past_last = vec.erase( std::next(vec.begin(),1), std::next(vec.begin(),4) );
        assert( std::next(vec.begin(),1) == past_last );
        assert( vec == ( sc::vector<int>{ 1, 5 } ) );
        assert( vec.size() == 2 );

        // removing a segment that reached the end.
        vec = { 1, 2, 3, 4, 5 };
        past_last = vec.erase( std::next(vec.begin(),2), vec.end() );
        assert( vec.end() == past_last );
        assert( vec == ( sc::vector<int>{ 1, 2 } ) );
        assert( vec.size() == 2 );

        // removing the entire vector.
        vec = { 1, 2, 3, 4, 5 };
        past_last = vec.erase( vec.begin(), vec.end() );
        assert( vec.end() == past_last );
        assert( vec.empty() );

        std::cout << ">>> Passed!\n\n";
    }
    {
        std::cout << ">>> Unit teste #" << ++n_unit << ": erase(pos).\n";

        // Initial vector.
        sc::vector<int> vec { 1, 2, 3, 4, 5 };

        // removing a single element.
        vec = { 1, 2, 3, 4, 5 };
        auto past_last = vec.erase( vec.begin() );
        assert( vec == ( sc::vector<int>{ 2, 3, 4, 5 } ) );
        assert( vec.begin() == past_last );
        assert( vec.size() == 4 );

        // removing a single element in the middle.
        vec = { 1, 2, 3, 4, 5 };
        past_last = vec.erase( std::next(vec.begin(),2) );
        assert( vec == ( sc::vector<int>{ 1, 2, 4, 5 } ) );
        assert( std::next(vec.begin(),2) == past_last );
        assert( vec.size() == 4 );

        // removing a single element at the end.
        vec = { 1, 2, 3, 4, 5 };
        past_last = vec.erase( std::next(vec.begin(),vec.size()-1 ) );
        assert( vec == ( sc::vector<int>{ 1, 2, 3, 4 } ) );
        assert( vec.end() == past_last );
        assert( vec.size() == 4 );

        std::cout << ">>> Passed!\n\n";
    }


    std::cout << "\n>>> Normal ending...\n\n";

    return EXIT_SUCCESS;
}

