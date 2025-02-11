//===-- RISCVCallingConv.h - RISC-V Custom CC Routines ----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the custom routines for the RISC-V Calling Convention.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/RISCVBaseInfo.h"
#include "llvm/CodeGen/CallingConvLower.h"

namespace llvm {

class DataLayout;
class RISCVTargetLowering;

/// RISCVCCAssignFn - This target-specific function extends the default
/// CCValAssign with additional information used to lower RISC-V calling
/// conventions.
typedef bool RISCVCCAssignFn(const DataLayout &DL, RISCVABI::ABI,
                             unsigned ValNo, MVT ValVT, MVT LocVT,
                             CCValAssign::LocInfo LocInfo,
                             ISD::ArgFlagsTy ArgFlags, CCState &State,
                             bool IsFixed, bool IsRet, Type *OrigTy,
                             const RISCVTargetLowering &TLI);

bool CC_RISCV(const DataLayout &DL, RISCVABI::ABI ABI, unsigned ValNo,
              MVT ValVT, MVT LocVT, CCValAssign::LocInfo LocInfo,
              ISD::ArgFlagsTy ArgFlags, CCState &State, bool IsFixed,
              bool IsRet, Type *OrigTy, const RISCVTargetLowering &TLI);

bool CC_RISCV_FastCC(const DataLayout &DL, RISCVABI::ABI ABI, unsigned ValNo,
                     MVT ValVT, MVT LocVT, CCValAssign::LocInfo LocInfo,
                     ISD::ArgFlagsTy ArgFlags, CCState &State, bool IsFixed,
                     bool IsRet, Type *OrigTy, const RISCVTargetLowering &TLI);

bool CC_RISCV_GHC(unsigned ValNo, MVT ValVT, MVT LocVT,
                  CCValAssign::LocInfo LocInfo, ISD::ArgFlagsTy ArgFlags,
                  CCState &State);

namespace RISCV {

ArrayRef<MCPhysReg> getArgGPRs(const RISCVABI::ABI ABI);

} // end namespace RISCV

} // end namespace llvm
