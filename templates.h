#include <bitset>
#include "t_128.h"
#include "pencilmarks.h"

struct templateIndex {
	std::bitset<46656> index;
	templateIndex& set(std::size_t pos) {
		index.set(pos);
		return *this;
	}
	templateIndex& reset(std::size_t pos) {
		index.reset(pos);
		return *this;
	}
	templateIndex& setAll() {
		index.set();
		return *this;
	}
	templateIndex& operator&=(const templateIndex& other) {
		index &= other.index;
		return *this;
	}
	std::size_t count() const noexcept {
		return index.count();
	}
	bool operator[](int i) const {
		return index[i];
	}
	templateIndex& setInverseOf(const templateIndex& other) {
		index = other.index;
		index.flip();
		return *this;
	}
	size_t first() const {
		return index._Find_first();
	}
	size_t next(size_t pos) const {
		return index._Find_next(pos);
	}
	constexpr size_t size() const {
		return index.size();
	}
	bool none() const {
		return index.none();
	}
	bool any() const {
		return index.any();
	}
};

struct templates {
	static bm128 allTemplates[46656];
	static templateIndex cellIndexes[81];
	static templateIndex cellInverseIndexes[81];
	static templateIndex disjointsIndexes[46656];
	static void init();
	//unsigned long long nSol(const char *p);
	templates();
	static unsigned long long solve(const pencilmarks& forbiddenValuePositions, char* res);
};

