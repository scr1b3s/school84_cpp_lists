#ifndef ITER_HPP
#define ITER_HPP

template<typename T, typename Func>
void iter(T* array, int length, Func function) {
    for (int i = 0; i < length; i++) {
        function(array[i]);
    }
}

#endif
