/* Copyright 2023 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_COMPILER_MLIR_TFRT_TRANSFORMS_IFRT_IFRT_BACKEND_COMPILER_H_
#define TENSORFLOW_COMPILER_MLIR_TFRT_TRANSFORMS_IFRT_IFRT_BACKEND_COMPILER_H_

#include <vector>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "mlir/IR/BuiltinOps.h"  // from @llvm-project
#include "tensorflow/compiler/mlir/tfrt/backend_compiler.h"
#include "tensorflow/core/tfrt/ifrt/ifrt_executable_registry.h"
#include "tensorflow/core/tfrt/ifrt/ifrt_model_context.h"
#include "tensorflow/core/tfrt/runtime/runtime.h"

namespace tensorflow {
namespace ifrt_serving {

// Implements the custom backend compiler for IFRT based serving in TFRT.
class IfrtBackendCompiler : public tensorflow::BackendCompiler {
 public:
  // Rewrites the tensorflow graph in MLIR for IFRT serving. The methods
  // extracts regions for IFRT execution on accelerator (e.g. TPU).
  absl::Status CompileTensorflow(
      tensorflow::tfrt_stub::ModelRuntimeContext& model_context,
      mlir::ModuleOp module) const override;

 private:
  absl::Status CompileTensorflowForIfrtServing(
      absl::string_view model_name, IfrtModelContext& ifrt_model_context,
      mlir::ModuleOp module) const;

  absl::StatusOr<std::vector<ServingExecutableRegistry::Handle>>
  CompileAndRegisterIfrtPrograms(absl::string_view model_name,
                                 mlir::ModuleOp module) const;
};

}  // namespace ifrt_serving
}  // namespace tensorflow

#endif  // TENSORFLOW_COMPILER_MLIR_TFRT_TRANSFORMS_IFRT_IFRT_BACKEND_COMPILER_H_
