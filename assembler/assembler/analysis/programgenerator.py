from assembler.analysis.ovmclass import OVMClass
from assembler.analysis.ovmfunction import OVMFunction
from assembler.analysis.bytecoderesolver import ResolvedFunction, ResolvedFunctionContext


class ProgramGenerator:

    def __init__(self):
        self.last_class_id = -1

    def __generate_class(self, resolved_class: ResolvedFunctionContext) -> OVMClass:
        new_id = self.last_class_id + 1
        self.last_class_id = new_id

        return OVMClass(resolved_class.context_name, new_id)

    def __generate_function(self, function: ResolvedFunction) -> OVMFunction:
