#ifndef DIRECTION_HPP
#define DIRECTION_HPP

namespace rugby {

// Structs

/**
 * A direction represents a vector of movement in a 2D grid.
 */
struct direction_t {
 public:
  // Public instance variables
  int i;
  int j;
};

namespace DIR {

constexpr direction_t KEEP       {  0,  0 };
constexpr direction_t UP         { -1,  0 };
constexpr direction_t UP_RIGHT   { -1,  1 };
constexpr direction_t RIGHT      {  0,  1 };
constexpr direction_t DOWN_RIGHT {  1,  1 };
constexpr direction_t DOWN       {  1,  0 };
constexpr direction_t DOWN_LEFT  {  1, -1 };
constexpr direction_t LEFT       {  0, -1 };
constexpr direction_t UP_LEFT    { -1, -1 };

}  // namespace DIR

}  // namespace rugby

#endif // DIRECTION_HPP
