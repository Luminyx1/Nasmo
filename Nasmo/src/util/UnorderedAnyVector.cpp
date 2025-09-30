#include <nsm/util/UnorderedAnyVector.h>
#include <nsm/debug/Assert.h>

nsm::UnorderedAnyVector::UnorderedAnyVector()
    : mBuffer(nullptr)
    , mBufferCapacity(0)
    , mElementSize(0)
    , mElementCount(0)
{ }

nsm::UnorderedAnyVector::~UnorderedAnyVector() {
    delete[] mBuffer;
}

void nsm::UnorderedAnyVector::addElement() {
    NSM_ASSERT(mElementSize > 0, "Element size was unset");
    
    mElementCount++;
    
    const std::size_t newSize = mElementCount * mElementSize;
    
    if (mBuffer == nullptr || newSize > mBufferCapacity) {
        this->shrinkToFit(); // actually grows in this case
    }
}

void nsm::UnorderedAnyVector::removeElement(const std::size_t index) {
    NSM_ASSERT(mBuffer != nullptr, "Buffer is nullptr");
    NSM_ASSERT(mElementSize > 0, "Element size is 0");
    NSM_ASSERT(index < mElementCount, "Index out of bounds");
    
    if (index != mElementCount - 1) { // removed != last
        // removed = last
        std::memcpy(&mBuffer[index * mElementSize], &mBuffer[mElementSize * mElementCount - mElementSize], mElementSize);
    }

    mElementCount--;
}

void nsm::UnorderedAnyVector::shrinkToFit() { // It still shrinks if you removed a lot of entries since removeElement does a swap only and keeps the bigger buffer
    f32 cGrowthFactor = 1.5f;
    
    if (mBuffer == nullptr) {
        cGrowthFactor = 4.0f;
    }
    
    const std::size_t newSize = mElementCount * mElementSize * cGrowthFactor;
    
    u8* newBuffer = new u8[newSize];
    
    if (mBuffer != nullptr) {
        std::memcpy(newBuffer, mBuffer, mBufferCapacity);
        delete[] mBuffer;
    }
    
    mBuffer = newBuffer;
    mBufferCapacity = newSize;
}

void nsm::UnorderedAnyVector::setElementData(const std::size_t index, const void* data) {
    NSM_ASSERT(mBuffer != nullptr, "Buffer is nullptr");
    NSM_ASSERT(mElementSize > 0, "Element size is 0");
    NSM_ASSERT(index < mElementCount, "Index out of bounds");

    std::memcpy(static_cast<u8*>(mBuffer) + (mElementSize * index), data, mElementSize);
}

void nsm::UnorderedAnyVector::setElementSize(const std::size_t elementSize) {
    NSM_ASSERT(mElementCount == 0, "Cannot change element size on a non-empty vector");
    
    mElementSize = elementSize;
}
