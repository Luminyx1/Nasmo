#pragma once

#include <nsm/Common.h>

namespace nsm {

    class UnorderedAnyVector {
    public:
        UnorderedAnyVector();
        ~UnorderedAnyVector();
        
        UnorderedAnyVector(UnorderedAnyVector&) = delete;
        UnorderedAnyVector& operator=(UnorderedAnyVector&) = delete;

        [[nodiscard]] void* getBuffer() const { return mBuffer; }
        [[nodiscard]] std::size_t getElementSize() const { return mElementSize; }
        [[nodiscard]] std::size_t getElementCount() const { return mElementCount; }

        void addElement();
        void removeElement(const std::size_t index);
        void shrinkToFit();

        void setElementData(const std::size_t index, const void* data);
        void setElementSize(const std::size_t elementSize);

    private:
        u8* mBuffer;
        std::size_t mBufferCapacity;
        std::size_t mElementSize;
        std::size_t mElementCount;
    };

}
