	using namespace std;
        #include "dsexceptions.h"
	#include <vector>

        template <class Comparable>
        class BinaryHeap
        {
          public:
            explicit BinaryHeap( int capacity = 100 );

            bool isEmpty( ) const;
            bool isFull( ) const;
            const Comparable & findMin( );
        	const Comparable & findMax( );
	    	int Height () const;
			void printLtSubtree();
            void insert( const Comparable & x );
            void deleteMin( );
			void printLeaves();
            void deleteMin( Comparable & minItem );
            void makeEmpty( );

          private:
            int currentSize;  // Number of elements in heap
            vector<Comparable> array;        // The heap array

            void buildHeap( );
			void printLeaves(int i);
            void percolateDown( int hole );
            void printLtSubtree (int i);
        };

        #include "BinaryHeap.cpp"
