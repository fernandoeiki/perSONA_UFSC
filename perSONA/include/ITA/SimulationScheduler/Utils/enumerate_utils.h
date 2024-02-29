#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_ENUMERATE_UTILS
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_ENUMERATE_UTILS
#include <iterator>

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace Utils
		{
			// Enumerate range based for loops taken from:
			// https://www.numbercrunch.de/blog/2018/02/range-based-for-loops-with-counters/

			// wraps an iterator into a pair of an iterator and an integer index
			template<typename IteratorType>
			class EnumerateIterator
			{
			public:
				using Iterator  = IteratorType;
				using Reference = typename std::iterator_traits<Iterator>::reference;
				using IndexType = typename std::iterator_traits<Iterator>::difference_type;

			private:
				Iterator iter;
				IndexType index = 0;

			public:
				EnumerateIterator( ) = delete;
				explicit EnumerateIterator( Iterator iter, IndexType start ) : iter( iter ), index( start ) {}
				EnumerateIterator& operator++( )
				{
					++iter;
					++index;
					return *this;
				}
				bool operator==( const EnumerateIterator& other ) const { return iter == other.iter; }
				bool operator!=( const EnumerateIterator& other ) const { return iter != other.iter; }
				std::pair<Reference, const IndexType&> operator*( ) const { return { *iter, index }; }
			};

			// pseudo container, wraps a range given by two iterators [first, last)
			// into a range of enumerate iterators
			template<typename IteratorType>
			class EnumerateRange
			{
			public:
				using Iterator  = EnumerateIterator<IteratorType>;
				using IndexType = typename std::iterator_traits<IteratorType>::difference_type;

			private:
				const IteratorType first, last;
				const IndexType start;

			public:
				EnumerateRange( ) = delete;
				explicit EnumerateRange( IteratorType first, IteratorType last, IndexType start = 0 ) : first( first ), last( last ), start( start ) {}
				Iterator begin( ) const { return Iterator( first, start ); }
				Iterator end( ) const { return Iterator( last, start ); }
			};

			// convert a container into a range of enumerate iterators
			template<typename ContainerType>
			EnumerateRange<typename ContainerType::iterator> Enumerate( ContainerType& content,
			                                                            typename std::iterator_traits<typename ContainerType::iterator>::difference_type start = 0 )
			{
				using ::std::begin;
				using ::std::end;
				return EnumerateRange<typename ContainerType::iterator>( begin( content ), end( content ), start );
			}

			// convert a range given by two iterators [first, last) into a range
			// of enumerate iterators
			template<typename IteratorType>
			EnumerateRange<IteratorType> Enumerate( IteratorType first, IteratorType last, typename std::iterator_traits<IteratorType>::difference_type start = 0 )
			{
				return EnumerateRange<IteratorType>( first, last, start );
			}

			// convert an initializer list into a range of enumerate iterators
			template<typename Type>
			EnumerateRange<typename std::initializer_list<Type>::iterator> Enumerate( const std::initializer_list<Type>& content, std::ptrdiff_t start = 0 )
			{
				return EnumerateRange<typename std::initializer_list<Type>::iterator>( content.begin( ), content.end( ), start );
			}
		} // namespace Utils
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_ENUMERATE_UTILS