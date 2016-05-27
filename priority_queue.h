#pragma once

#include <algorithm>
#include <vector>

namespace util {

template <typename T, typename Cmp = std::less<T>>
class priority_queue {
public:
    T& top() {
        return m_heap[0];
    }

    const T& top() const {
        return m_heap[0];
    }

    void pop() {
        int last_leaf = m_size - 1;
        std::swap(m_heap[0], m_heap[last_leaf]);
        --m_size;
        sift_down(0);
    }

    template <typename V>
    void push(V &&v) {
        if (m_size == m_heap.size()) {
            m_heap.push_back(std::forward<V>(v));
        } else {
            m_heap[m_size] = std::forward<V>(v);
        }

        ++m_size;

        sift_up(m_size - 1);
    }

    size_t size() const {
        return m_size;
    }

    bool empty() const {
        return m_size == 0;
    }

private:
    void sift_up(int i) {
        int p = parent(i);

        while (p >= 0 && m_cmp(m_heap[p], m_heap[i])) {
            std::swap(m_heap[p], m_heap[i]);
            sift_up(p);
        }
    }

    void sift_down(int i) {
        int left = left_child(i);
        int right = right_child(i);

        int max = i;
        if (left < m_size && m_cmp(m_heap[max], m_heap[left])) {
            max = left;
        }

        if (right < m_size && m_cmp(m_heap[max], m_heap[right])) {
            max = right;
        }

        if (max != i) {
            std::swap(m_heap[i], m_heap[max]);
            sift_down(max);
        }
    }

    int parent(int i) {
        return (i - 1) / 2;
    }

    int left_child(int i) {
        return 2 * i + 1;
    }

    int right_child(int i) {
        return 2 * i + 2;
    }

private:
    Cmp m_cmp;
    int m_size = 0;
    std::vector<T> m_heap;
};

} // namespace util
