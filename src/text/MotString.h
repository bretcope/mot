#ifndef MOT_GOTSTRING_H
#define MOT_GOTSTRING_H


#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <ostream>

namespace mot
{
    class MotString
    {
    private:
        const char* _data;
        uint32_t _byteCount;
        mutable uint32_t _hashCode = 0; // lazy loaded
        mutable uint32_t _charCount = 0; // lazy loaded
        bool _isOwnerOfData;

    public:
        /**
         *
         * @param data The raw UTF-8 string.
         * @param byteCount The number of bytes which are meaningful (excludes the null terminator).
         * @param transferOwnership If true, the data will be deallocated when the MotString is destructed.
         */
        MotString(const char* data, uint32_t byteCount, bool transferOwnership);

        /**
         * Creates a MotString based off of a null-terminated C string.
         *
         * \warning The MotString does not control the lifetime of the C string. This constructor is primarily intended for creating MotStrings based off of
         * string literals.
         */
        explicit MotString(const char* str);

        MotString(const MotString&);

        MotString(MotString&&) noexcept;

        ~MotString();

        MotString& operator=(MotString) noexcept;

        friend std::ostream& operator<<(std::ostream& os, const MotString& s);

        friend void swap(MotString& a, MotString& b) noexcept;

        /**
         * Returns the number of bytes which are meaningful (excludes the null terminator).
         */
        uint32_t ByteLength() const;

        /**
         * Returns the number of unicode code points in the string.
         */
        uint32_t CharacterCount() const;

        /**
         * Returns a case-insensitive hash code for the string.
         */
        uint32_t HashCode() const;

        /**
         * Returns zero if the two strings have identical values, a negative value if a < b, and a positive if a > b. The ordering is based on the binary encoding.
         */
        static int Compare(const MotString* a, const MotString* b);

        /**
         * Compares a and b in a case insensitive way. Returns 0 when a == b, negative when a < b, and positive when a > b. The comparison is based on the
         * uppercase variant of each code point in the string.
         */
        static int CompareCaseInsensitive(const MotString* a, const MotString* b);

        /**
         * Returns true if the two strings have identical values.
         */
        static bool AreEqual(const MotString* a, const MotString* b);

        /**
         * Returns true if the two strings are equal when compared in a case-insensitive way.
         */
        static bool AreCaseInsensitiveEqual(const MotString* a, const MotString* b);

        bool IsEqualTo(const MotString* str) const;

        bool IsCaseInsensitiveEqualTo(const MotString* str) const;

        /**
         * Prints the string to a file stream.
         */
        void Print(FILE* stream) const;

        /**
         * Returns a pointer to an empty MotString. Use this method to avoid allocating every time you need an empty string on the heap.
         */
        static const MotString* Empty();

    private:

        /**
         * Returns zero if the two strings are equivalent. Otherwise, non-zero.
         * @param a String to compare.
         * @param b String to compare.
         * @param caseSensitive If true, the strings must be an exact match.
         * @param orderedResult If true, the return value guaranteed to be negative if a < b and positive if a > b. If false, the return value is only guaranteed
         * to be non-zero when the strings are not equal.
         */
        static int CompareImpl(const MotString* a, const MotString* b, bool caseSensitive, bool orderedResult);

        void CalculateHashAndCharacterCount() const;
    };
}

#endif //MOT_GOTSTRING_H