/* Copyright (c) 2010-present Advanced Micro Devices, Inc.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE. */

#ifndef GPUBLIT_HPP_
#define GPUBLIT_HPP_

#include "top.hpp"
#include "platform/command.hpp"
#include "device/gpu/gpudefs.hpp"
#include "device/device.hpp"
#include "device/blit.hpp"

/*! \addtogroup GPU Blit Implementation
 *  @{
 */

//! GPU Blit Manager Implementation
namespace gpu {

class Device;
class Kernel;
class Memory;
class VirtualGPU;

//! DMA Blit Manager
class DmaBlitManager : public device::HostBlitManager {
 public:
  //! Constructor
  DmaBlitManager(VirtualGPU& gpu,       //!< Virtual GPU to be used for blits
                 Setup setup = Setup()  //!< Specifies HW accelerated blits
                 );

  //! Destructor
  virtual ~DmaBlitManager() {}

  //! Creates DmaBlitManager object
  virtual bool create(amd::Device& device) { return true; }

  //! Copies a buffer object to system memory
  virtual bool readBuffer(device::Memory& srcMemory,   //!< Source memory object
                          void* dstHost,               //!< Destination host memory
                          const amd::Coord3D& origin,  //!< Source origin
                          const amd::Coord3D& size,    //!< Size of the copy region
                          bool entire = false          //!< Entire buffer will be updated
                          ) const;

  //! Copies a buffer object to system memory
  virtual bool readBufferRect(device::Memory& srcMemory,        //!< Source memory object
                              void* dstHost,                    //!< Destinaiton host memory
                              const amd::BufferRect& bufRect,   //!< Source rectangle
                              const amd::BufferRect& hostRect,  //!< Destination rectangle
                              const amd::Coord3D& size,         //!< Size of the copy region
                              bool entire = false               //!< Entire buffer will be updated
                              ) const;

  //! Copies an image object to system memory
  virtual bool readImage(device::Memory& srcMemory,   //!< Source memory object
                         void* dstHost,               //!< Destination host memory
                         const amd::Coord3D& origin,  //!< Source origin
                         const amd::Coord3D& size,    //!< Size of the copy region
                         size_t rowPitch,             //!< Row pitch for host memory
                         size_t slicePitch,           //!< Slice pitch for host memory
                         bool entire = false          //!< Entire buffer will be updated
                         ) const;

  //! Copies system memory to a buffer object
  virtual bool writeBuffer(const void* srcHost,         //!< Source host memory
                           device::Memory& dstMemory,   //!< Destination memory object
                           const amd::Coord3D& origin,  //!< Destination origin
                           const amd::Coord3D& size,    //!< Size of the copy region
                           bool entire = false          //!< Entire buffer will be updated
                           ) const;

  //! Copies system memory to a buffer object
  virtual bool writeBufferRect(const void* srcHost,              //!< Source host memory
                               device::Memory& dstMemory,        //!< Destination memory object
                               const amd::BufferRect& hostRect,  //!< Destination rectangle
                               const amd::BufferRect& bufRect,   //!< Source rectangle
                               const amd::Coord3D& size,         //!< Size of the copy region
                               bool entire = false               //!< Entire buffer will be updated
                               ) const;

  //! Copies system memory to an image object
  virtual bool writeImage(const void* srcHost,         //!< Source host memory
                          device::Memory& dstMemory,   //!< Destination memory object
                          const amd::Coord3D& origin,  //!< Destination origin
                          const amd::Coord3D& size,    //!< Size of the copy region
                          size_t rowPitch,             //!< Row pitch for host memory
                          size_t slicePitch,           //!< Slice pitch for host memory
                          bool entire = false          //!< Entire buffer will be updated
                          ) const;

  //! Copies a buffer object to another buffer object
  virtual bool copyBuffer(device::Memory& srcMemory,      //!< Source memory object
                          device::Memory& dstMemory,      //!< Destination memory object
                          const amd::Coord3D& srcOrigin,  //!< Source origin
                          const amd::Coord3D& dstOrigin,  //!< Destination origin
                          const amd::Coord3D& size,       //!< Size of the copy region
                          bool entire = false             //!< Entire buffer will be updated
                          ) const;

  //! Copies a buffer object to another buffer object
  virtual bool copyBufferRect(device::Memory& srcMemory,       //!< Source memory object
                              device::Memory& dstMemory,       //!< Destination memory object
                              const amd::BufferRect& srcRect,  //!< Source rectangle
                              const amd::BufferRect& dstRect,  //!< Destination rectangle
                              const amd::Coord3D& size,        //!< Size of the copy region
                              bool entire = false              //!< Entire buffer will be updated
                              ) const;

  //! Copies an image object to a buffer object
  virtual bool copyImageToBuffer(device::Memory& srcMemory,      //!< Source memory object
                                 device::Memory& dstMemory,      //!< Destination memory object
                                 const amd::Coord3D& srcOrigin,  //!< Source origin
                                 const amd::Coord3D& dstOrigin,  //!< Destination origin
                                 const amd::Coord3D& size,       //!< Size of the copy region
                                 bool entire = false,            //!< Entire buffer will be updated
                                 size_t rowPitch = 0,            //!< Pitch for buffer
                                 size_t slicePitch = 0           //!< Slice for buffer
                                 ) const;

  //! Copies a buffer object to an image object
  virtual bool copyBufferToImage(device::Memory& srcMemory,      //!< Source memory object
                                 device::Memory& dstMemory,      //!< Destination memory object
                                 const amd::Coord3D& srcOrigin,  //!< Source origin
                                 const amd::Coord3D& dstOrigin,  //!< Destination origin
                                 const amd::Coord3D& size,       //!< Size of the copy region
                                 bool entire = false,            //!< Entire buffer will be updated
                                 size_t rowPitch = 0,            //!< Pitch for buffer
                                 size_t slicePitch = 0           //!< Slice for buffer
                                 ) const;

  //! Copies an image object to another image object
  virtual bool copyImage(device::Memory& srcMemory,      //!< Source memory object
                         device::Memory& dstMemory,      //!< Destination memory object
                         const amd::Coord3D& srcOrigin,  //!< Source origin
                         const amd::Coord3D& dstOrigin,  //!< Destination origin
                         const amd::Coord3D& size,       //!< Size of the copy region
                         bool entire = false             //!< Entire buffer will be updated
                         ) const;

 protected:
  static constexpr uint MaxPinnedBuffers = 4;

  //! Synchronizes the blit operations if necessary
  inline void synchronize() const;

  //! Returns the virtual GPU object
  VirtualGPU& gpu() const { return static_cast<VirtualGPU&>(vDev_); }

  //! Returns the GPU device object
  const Device& dev() const { return static_cast<const Device&>(dev_); };

  inline Memory& gpuMem(device::Memory& mem) const;

  //! Pins host memory for GPU access
  amd::Memory* pinHostMemory(const void* hostMem,  //!< Host memory pointer
                             size_t pinSize,       //!< Host memory size
                             size_t& partial       //!< Extra offset for memory alignment
                             ) const;

  const size_t MinSizeForPinnedTransfer;
  bool completeOperation_;  //!< DMA blit manager must complete operation
  amd::Context* context_;   //!< A dummy context

 private:
  //! Disable copy constructor
  DmaBlitManager(const DmaBlitManager&);

  //! Disable operator=
  DmaBlitManager& operator=(const DmaBlitManager&);

  //! Reads video memory, using a staged buffer
  bool readMemoryStaged(Memory& srcMemory,  //!< Source memory object
                        void* dstHost,      //!< Destination host memory
                        Memory** xferBuf,   //!< Staged buffer for read
                        size_t origin,      //!< Original offset in the source memory
                        size_t& offset,     //!< Offset for the current copy pointer
                        size_t& totalSize,  //!< Total size for copy region
                        size_t xferSize     //!< Transfer size
                        ) const;

  //! Write into video memory, using a staged buffer
  bool writeMemoryStaged(const void* srcHost,  //!< Source host memory
                         Memory& dstMemory,    //!< Destination memory object
                         Memory& xferBuf,      //!< Staged buffer for write
                         size_t origin,        //!< Original offset in the destination memory
                         size_t& offset,       //!< Offset for the current copy pointer
                         size_t& totalSize,    //!< Total size for the copy region
                         size_t xferSize       //!< Transfer size
                         ) const;
};

//! Kernel Blit Manager
class KernelBlitManager : public DmaBlitManager {
 public:
  enum {
    BlitCopyImage = 0,
    BlitCopyImage1DA,
    BlitCopyImageToBuffer,
    BlitCopyBufferToImage,
    BlitCopyBufferRect,
    BlitCopyBufferRectAligned,
    BlitCopyBuffer,
    BlitCopyBufferAligned,
    FillBuffer,
    FillImage,
    Scheduler,
    BlitTotal
  };

  //! Constructor
  KernelBlitManager(VirtualGPU& gpu,       //!< Virtual GPU to be used for blits
                    Setup setup = Setup()  //!< Specifies HW accelerated blits
                    );

  //! Destructor
  virtual ~KernelBlitManager();

  //! Creates DmaBlitManager object
  virtual bool create(amd::Device& device);

  //! Copies a buffer object to another buffer object
  virtual bool copyBufferRect(device::Memory& srcMemory,         //!< Source memory object
                              device::Memory& dstMemory,         //!< Destination memory object
                              const amd::BufferRect& srcRectIn,  //!< Source rectangle
                              const amd::BufferRect& dstRectIn,  //!< Destination rectangle
                              const amd::Coord3D& sizeIn,        //!< Size of the copy region
                              bool entire = false                //!< Entire buffer will be updated
                              ) const;

  //! Copies a buffer object to system memory
  virtual bool readBuffer(device::Memory& srcMemory,   //!< Source memory object
                          void* dstHost,               //!< Destination host memory
                          const amd::Coord3D& origin,  //!< Source origin
                          const amd::Coord3D& size,    //!< Size of the copy region
                          bool entire = false          //!< Entire buffer will be updated
                          ) const;

  //! Copies a buffer object to system memory
  virtual bool readBufferRect(device::Memory& srcMemory,        //!< Source memory object
                              void* dstHost,                    //!< Destinaiton host memory
                              const amd::BufferRect& bufRect,   //!< Source rectangle
                              const amd::BufferRect& hostRect,  //!< Destination rectangle
                              const amd::Coord3D& size,         //!< Size of the copy region
                              bool entire = false               //!< Entire buffer will be updated
                              ) const;

  //! Copies system memory to a buffer object
  virtual bool writeBuffer(const void* srcHost,         //!< Source host memory
                           device::Memory& dstMemory,   //!< Destination memory object
                           const amd::Coord3D& origin,  //!< Destination origin
                           const amd::Coord3D& size,    //!< Size of the copy region
                           bool entire = false          //!< Entire buffer will be updated
                           ) const;

  //! Copies system memory to a buffer object
  virtual bool writeBufferRect(const void* srcHost,              //!< Source host memory
                               device::Memory& dstMemory,        //!< Destination memory object
                               const amd::BufferRect& hostRect,  //!< Destination rectangle
                               const amd::BufferRect& bufRect,   //!< Source rectangle
                               const amd::Coord3D& size,         //!< Size of the copy region
                               bool entire = false               //!< Entire buffer will be updated
                               ) const;

  //! Copies a buffer object to an image object
  virtual bool copyBuffer(device::Memory& srcMemory,      //!< Source memory object
                          device::Memory& dstMemory,      //!< Destination memory object
                          const amd::Coord3D& srcOrigin,  //!< Source origin
                          const amd::Coord3D& dstOrigin,  //!< Destination origin
                          const amd::Coord3D& size,       //!< Size of the copy region
                          bool entire = false             //!< Entire buffer will be updated
                          ) const;

  //! Copies a buffer object to an image object
  virtual bool copyBufferToImage(device::Memory& srcMemory,      //!< Source memory object
                                 device::Memory& dstMemory,      //!< Destination memory object
                                 const amd::Coord3D& srcOrigin,  //!< Source origin
                                 const amd::Coord3D& dstOrigin,  //!< Destination origin
                                 const amd::Coord3D& size,       //!< Size of the copy region
                                 bool entire = false,            //!< Entire buffer will be updated
                                 size_t rowPitch = 0,            //!< Pitch for buffer
                                 size_t slicePitch = 0           //!< Slice for buffer
                                 ) const;

  //! Copies an image object to a buffer object
  virtual bool copyImageToBuffer(device::Memory& srcMemory,      //!< Source memory object
                                 device::Memory& dstMemory,      //!< Destination memory object
                                 const amd::Coord3D& srcOrigin,  //!< Source origin
                                 const amd::Coord3D& dstOrigin,  //!< Destination origin
                                 const amd::Coord3D& size,       //!< Size of the copy region
                                 bool entire = false,            //!< Entire buffer will be updated
                                 size_t rowPitch = 0,            //!< Pitch for buffer
                                 size_t slicePitch = 0           //!< Slice for buffer
                                 ) const;

  //! Copies an image object to another image object
  virtual bool copyImage(device::Memory& srcMemory,      //!< Source memory object
                         device::Memory& dstMemory,      //!< Destination memory object
                         const amd::Coord3D& srcOrigin,  //!< Source origin
                         const amd::Coord3D& dstOrigin,  //!< Destination origin
                         const amd::Coord3D& size,       //!< Size of the copy region
                         bool entire = false             //!< Entire buffer will be updated
                         ) const;

  //! Copies an image object to system memory
  virtual bool readImage(device::Memory& srcMemory,   //!< Source memory object
                         void* dstHost,               //!< Destination host memory
                         const amd::Coord3D& origin,  //!< Source origin
                         const amd::Coord3D& size,    //!< Size of the copy region
                         size_t rowPitch,             //!< Row pitch for host memory
                         size_t slicePitch,           //!< Slice pitch for host memory
                         bool entire = false          //!< Entire buffer will be updated
                         ) const;

  //! Copies system memory to an image object
  virtual bool writeImage(const void* srcHost,         //!< Source host memory
                          device::Memory& dstMemory,   //!< Destination memory object
                          const amd::Coord3D& origin,  //!< Destination origin
                          const amd::Coord3D& size,    //!< Size of the copy region
                          size_t rowPitch,             //!< Row pitch for host memory
                          size_t slicePitch,           //!< Slice pitch for host memory
                          bool entire = false          //!< Entire buffer will be updated
                          ) const;

  //! Fills a buffer memory with a pattern data
  virtual bool fillBuffer(device::Memory& memory,      //!< Memory object to fill with pattern
                          const void* pattern,         //!< Pattern data
                          size_t patternSize,          //!< Pattern size
                          const amd::Coord3D& origin,  //!< Destination origin
                          const amd::Coord3D& size,    //!< Size of the copy region
                          bool entire = false          //!< Entire buffer will be updated
                          ) const;

  //! Fills an image memory with a pattern data
  virtual bool fillImage(device::Memory& dstMemory,   //!< Memory object to fill with pattern
                         const void* pattern,         //!< Pattern data
                         const amd::Coord3D& origin,  //!< Destination origin
                         const amd::Coord3D& size,    //!< Size of the copy region
                         bool entire = false          //!< Entire buffer will be updated
                         ) const;

  //! Fills an image memory with a pattern data
  virtual bool runScheduler(device::Memory& vqueue,  //!< Memory object for virtual queue
                            device::Memory& params,  //!< Extra arguments for the scheduler
                            uint paramIdx,           //!< Parameter index
                            uint threads             //!< Number of scheduling threads
                            ) const;

 private:
  static constexpr size_t MaxXferBuffers = 2;
  static constexpr uint TransferSplitSize = 3;

  //! Copies a buffer object to an image object
  bool copyBufferToImageKernel(device::Memory& srcMemory,      //!< Source memory object
                               device::Memory& dstMemory,      //!< Destination memory object
                               const amd::Coord3D& srcOrigin,  //!< Source origin
                               const amd::Coord3D& dstOrigin,  //!< Destination origin
                               const amd::Coord3D& size,       //!< Size of the copy region
                               bool entire = false,            //!< Entire buffer will be updated
                               size_t rowPitch = 0,            //!< Pitch for buffer
                               size_t slicePitch = 0           //!< Slice for buffer
                               ) const;

  //! Copies an image object to a buffer object
  bool copyImageToBufferKernel(device::Memory& srcMemory,      //!< Source memory object
                               device::Memory& dstMemory,      //!< Destination memory object
                               const amd::Coord3D& srcOrigin,  //!< Source origin
                               const amd::Coord3D& dstOrigin,  //!< Destination origin
                               const amd::Coord3D& size,       //!< Size of the copy region
                               bool entire = false,            //!< Entire buffer will be updated
                               size_t rowPitch = 0,            //!< Pitch for buffer
                               size_t slicePitch = 0           //!< Slice for buffer
                               ) const;

  //! Creates a program for all blit operations
  bool createProgram(Device& device  //!< Device object
                     );

  //! Creates a view memory object
  Memory* createView(const Memory& parent,    //!< Parent memory object
                     const CalFormat& format  //!< The new format for a view
                     ) const;

  //! Disable copy constructor
  KernelBlitManager(const KernelBlitManager&);

  //! Disable operator=
  KernelBlitManager& operator=(const KernelBlitManager&);

  amd::Program* program_;                     //!< GPU program obejct
  amd::Kernel* kernels_[BlitTotal];           //!< GPU kernels for blit
  amd::Memory* constantBuffer_;               //!< An internal CB for blits
  amd::Memory* xferBuffers_[MaxXferBuffers];  //!< Transfer buffers for images
  size_t xferBufferSize_;                     //!< Transfer buffer size
  amd::Monitor* lockXferOps_;                 //!< Lock transfer operation
};

static constexpr const char* BlitName[KernelBlitManager::BlitTotal] = {
    "copyImage",         "copyImage1DA",      "copyImageToBuffer",
    "copyBufferToImage", "copyBufferRect",    "copyBufferRectAligned",
    "copyBuffer",        "copyBufferAligned", "fillBuffer",
    "fillImage",         "scheduler",
};

/*@}*/} // namespace gpu

#endif /*GPUBLIT_HPP_*/
