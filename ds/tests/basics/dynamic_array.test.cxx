#include <ut.hpp>
#include <src/dynamic_array.mxx>
// import ds.dynamic_array;
// import boost.ut;

using namespace boost::ut;
using namespace boost::ut::bdd;

suite dynamic_array_test = [] {
  "dynamic array test"_test = [] {
    given("Give a dynamic array of {5,2}") = [] {
      auto dyna_array = ds::dynamic_array<int>({ 5, 2 });

      when("When the dynamic_array is copied") = [&dyna_array] {
        auto dyna_array_copy = dyna_array;
        then("dyanmic array copy must == {5,2}")
            = [&dyna_array, &dyna_array_copy] {
                expect(that % dyna_array_copy.size() == dyna_array.size());
              };
      };

      when("When dynamic array is moved") = [&dyna_array] {
        auto dyna_size = dyna_array.size();
        auto dyna_array_moved = std::move(dyna_array);
        then("Then dynamic array is in moved from state and the new move "
             "constracted array is that of the previous dynamic array")
            = [&dyna_array, &dyna_array_moved, &dyna_size] {
                expect(that % dyna_array.size() == 0UL);
                expect(that % dyna_array_moved.size() == dyna_size);
              };
      };

      when("When new array is constructed with capacity 2") = [] {
        auto array = ds::dynamic_array<int>(2);
        then("Then size is 0 capacity 2") = [&array] {
          expect(that % array.size() == 0UL);
          expect(that % array.capacity() == 2UL);
        };
        when("When push_back(number) is called") = [&array] {
          array.push_back(1);
          then("with push_back(number) size increase and container has number")
              = [&array] { expect(that % array.size() == 1UL); };
        };
        when("When pop_back() is called") = [&array] {
          array.pop_back();
          then("Then last element removed and size decrease")
              = [&array] { expect(that % array.size() == 0UL); };
        };
      };
    };
  };
};
