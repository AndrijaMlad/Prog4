#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

class SSOString {
private:
    struct LongString {
        unsigned char flag;
        short sz;
        short cap;
        char* array;
    };

    static constexpr int SHORT_CAP = sizeof(LongString) - 2;

    struct ShortString {
        unsigned char flag;
        char array[SHORT_CAP + 1];
    };

    union Storage {
        ShortString small;
        LongString large;
    };

    Storage storage;

    bool isShort() const {
        return storage.small.flag & 1;
    }

    char* data() {
        if (isShort())
            return storage.small.array;

        return storage.large.array;
    }

    const char* data() const {
        if (isShort())
            return storage.small.array;

        return storage.large.array;
    }

    void init(int n) {
        if (n > 32767)
            throw length_error("String is too long");

        if (n <= SHORT_CAP) {
            storage.small = ShortString{};
            storage.small.flag = (n << 1) | 1;
        }
        else {
            char* p = new char[n + 1];

            storage.large = LongString{};
            storage.large.flag = 0;
            storage.large.sz = n;
            storage.large.cap = n;
            storage.large.array = p;
        }

        data()[n] = '\0';
    }

    void release() {
        if (!isShort())
            delete[] storage.large.array;
    }

public:
    // Constructor
    SSOString(const char* str = "") {
        if (strlen(str) > 32767)
            throw length_error("String is too long");

        int n = strlen(str);

        init(n);

        memcpy(data(), str, n);
    }

    // Copy constructor
    SSOString(const SSOString& other) {
        int n = other.size();

        init(n);

        memcpy(data(), other.data(), n);
    }

    // Destructor
    ~SSOString() {
        release();
    }

    // Assignment operator
    SSOString& operator=(const SSOString& other) {
        if (this == &other)
            return *this;

        SSOString temp(other);

        release();

        storage = temp.storage;

        temp.storage.small = ShortString{};
        temp.storage.small.flag = 1;

        return *this;
    }

    int size() const {
        if (isShort())
            return storage.small.flag >> 1;

        return storage.large.sz;
    }

    int capacity() const {
        if (isShort())
            return SHORT_CAP;

        return storage.large.cap;
    }

    char& operator[](int i) {
        if (i < 0 || i >= size())
            throw out_of_range("Invalid index");

        return data()[i];
    }

    const char& operator[](int i) const {
        if (i < 0 || i >= size())
            throw out_of_range("Invalid index");

        return data()[i];
    }

    friend SSOString operator+(const SSOString& a,
                               const SSOString& b) {
        SSOString result;

        result.init(a.size() + b.size());

        memcpy(result.data(), a.data(), a.size());

        memcpy(result.data() + a.size(),
               b.data(), b.size());

        return result;
    }

    friend ostream& operator<<(ostream& out,
                               const SSOString& s) {
        return out.write(s.data(), s.size());
    }
};

int main() {
    SSOString a("Hello");
    SSOString b("World");

    SSOString c = a + b;
    SSOString d = c + c;

    cout << sizeof(SSOString) << endl;

    cout << c << " "
         << c.size() << " "
         << c.capacity() << endl;

    cout << d << " "
         << d.size() << " "
         << d.capacity() << endl;

    d = a;
    d[0] = 'Y';

    cout << d << endl;

    return 0;
}
