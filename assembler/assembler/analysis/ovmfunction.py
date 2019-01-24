from typing import List


class OVMFunctionImplementation:

    def __init__(self, interface_id: int, id: int):
        self.interface_id = interface_id
        self.id = id


class OVMFunction:

    def __init__(self, name: str, implementations: List[OVMFunctionImplementation]):
        self.name = name
        self.implementations = implementations
