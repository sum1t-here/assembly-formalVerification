//1.  0x6080604052
// 348015600e575f5ffd5b506101298061001c5f395ff3fe6080604052348015600e
// 575f5ffd5b50600436106030575f3560e01c806367d41eca146034578063e026c01714604c575b5f5
// ffd5b604a60048036038101906046919060a9565b6066565b005b6052606f565b604051605d919060
// dc565b60405180910390f35b805f8190555050565b5f5f54905090565b5f5ffd5b5f8190509190505
// 65b608b81607b565b81146094575f5ffd5b50565b5f8135905060a3816084565b92915050565b5f60
// 20828403121560bb5760ba6077565b5b5f60c6848285016097565b91505092915050565b60d681607b
// 565b82525050565b5f60208201905060ed5f83018460cf565b9291505056fea2646970667358221220
// ab4fb2620b8cbd118c3edf223dec46659496a851b292af84ecf9fda6d819f7a764736f6c634300081c0033

// 3 sections:
// 1. Contract creation
// 2. Runtime
// 3. Metadata

// 1. Contract creation
PUSH1 0x80
PUSH1 0x40
MSTORE
// 0x40 -> free mem ptr (indicates free mem slot)
// check for payable
// If someone sent value with this call revert!
// Otherwise jump to continue execution

CALLVALUE    // [msg.value]
DUP1         // [msg.value, msg.value]
ISZERO       // [msg.value == 0, msg.value]
PUSH1 0x0e   // [0x0e, msg.value == 0, msg.value]
JUMPI        // [msg.value]
PUSH0        // [0, msg.value]
PUSH0        // [0, 0, msg.value]
REVERT       // [msg.value]

// Jump dest if msg.value == 0
// sticks the runtime code on chain
JUMPDEST        // [msg.value]
POP             // []
PUSH2 0x0129    // [0x0129]
DUP1            // [0x0129, 0x0129]
PUSH2 0x001c    // [0x001c, 0x0129, 0x0129]
PUSH0           // [0x00, 0x001c, 0x0129, 0x0129]
CODECOPY        // [0x0129]        Memory: [runtime code]
PUSH0           // [0x00, 0x0129]
RETURN          // []
INVALID         // []       -> end of contract creation

// 2. Runtime code
// Entry point of all code
// free mem ptr
PUSH1 0x80
PUSH1 0x40
MSTORE

// checking for msg.value, and if given, reverting
CALLVALUE       // [msg.value]
DUP1            // [msg.value, msg.value]
ISZERO          // [msg.value == 0, msg.value]
PUSH1 0x0e      // [0x0e, msg.value == 0, msg.value]
JUMPI           // [msg.value]
// jump to "continue!"

PUSH0           // [0x00, msg.value]
PUSH0           // [0x00, 0x00, msg.value]
REVERT          // [msg.value]

// If msg.value == 0, start here
// continue!
// checking to see if there is enough calldata for a function selector
JUMPDEST        // [msg.value]
POP             // []
PUSH1 0x04      // [0x04]
CALLDATASIZE    // [calldata_size(size of the call data), 0x04]
LT              // [calldata_size < 0x04]
PUSH1 0x30      // [0x30, calldata_size < 0x04]
JUMPI           // []
// if calldata_size < 0x04, go to calldata_jump

// function dispatching in solidity
PUSH0               // [0]
CALLDATALOAD        // [32bytes of calldata]
PUSH1 0xe0          // [0xe0, 32bytes of calldata]
SHR                 // [calldata[0:4]] // function_selector

// function dispatching for updateNumberOfHorses
DUP1                // [func_selector, func_selector]
PUSH4 0x67d41eca    // [0x67d41eca, func_selector, func_selector]
EQ                  // [func_selector == 0x67d41eca, func_selector]
PUSH1 0x34          // [0x34, func_selector == 0x67d41eca, func_selector]
JUMPI               // [func_selector]
// if func_selector == 0x67d41eca -> set_number_of_horses

// function dispatching for readNumberOfHorses
DUP1                // [func_selector, func_selector]
PUSH4 0xe026c017    // [0xe026c017, func_selector, func_selector]
EQ                  // [func_selector == 0xe026c017, unc_selector]
PUSH1 0x4c
JUMPI
// if func_selector == 0xe026c017 -> get_number_of_horses

// calldata_jump
// Revert JUMPDEST
JUMPDEST            // []
PUSH0               // [0]
PUSH0               // [0,0]
REVERT              // []

JUMPDEST            // [func_selector]
PUSH1 0x4a          // [0x4a, func_selector]
PUSH1 0x04          // [0x04, 0x4a, func_selector]
DUP1                // [0x04, 0x04, 0x4a, func_selector]
CALLDATASIZE        // [calldatasize, 0x04, 0x04, 0x4a, func_selector]
SUB                 
DUP2
ADD
SWAP1
PUSH1 0x46
SWAP2
SWAP1
PUSH1 0xa9
JUMP
JUMPDEST
PUSH1 0x66
JUMP
JUMPDEST
STOP
JUMPDEST
PUSH1 0x52
PUSH1 0x6f
JUMP
JUMPDEST
PUSH1 0x40
MLOAD
PUSH1 0x5d
SWAP2
SWAP1
PUSH1 0xdc
JUMP
JUMPDEST
PUSH1 0x40
MLOAD
DUP1
SWAP2
SUB
SWAP1
RETURN
JUMPDEST
DUP1
PUSH0
DUP2
SWAP1
SSTORE
POP
POP
JUMP
JUMPDEST
PUSH0
PUSH0
SLOAD
SWAP1
POP
SWAP1
JUMP
JUMPDEST
PUSH0
PUSH0
REVERT
JUMPDEST
PUSH0
DUP2
SWAP1
POP
SWAP2
SWAP1
POP
JUMP
JUMPDEST
PUSH1 0x8b
DUP2
PUSH1 0x7b
JUMP
JUMPDEST
DUP2
EQ
PUSH1 0x94
JUMPI
PUSH0
PUSH0
REVERT
JUMPDEST
POP
JUMP
JUMPDEST
PUSH0
DUP2
CALLDATALOAD
SWAP1
POP
PUSH1 0xa3
DUP2
PUSH1 0x84
JUMP
JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP
JUMPDEST
PUSH0
PUSH1 0x20
DUP3
DUP5
SUB
SLT
ISZERO
PUSH1 0xbb
JUMPI
PUSH1 0xba
PUSH1 0x77
JUMP
JUMPDEST
JUMPDEST
PUSH0
PUSH1 0xc6
DUP5
DUP3
DUP6
ADD
PUSH1 0x97
JUMP
JUMPDEST
SWAP2
POP
POP
SWAP3
SWAP2
POP
POP
JUMP
JUMPDEST
PUSH1 0xd6
DUP2
PUSH1 0x7b
JUMP
JUMPDEST
DUP3
MSTORE
POP
POP
JUMP
JUMPDEST
PUSH0
PUSH1 0x20
DUP3
ADD
SWAP1
POP
PUSH1 0xed
PUSH0
DUP4
ADD
DUP5
PUSH1 0xcf
JUMP
JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
INVALID
INVALID
INVALID
PUSH3 0x0b8cbd
GT
DUP13
RETURNDATACOPY
INVALID
INVALID
RETURNDATASIZE
INVALID
CHAINID
PUSH6 0x9496a851b292
INVALID
DUP5
INVALID
INVALID
REVERT
INVALID
INVALID
NOT
INVALID
INVALID
PUSH5 0x736f6c6343
STOP
ADDMOD
SHR
STOP
CALLER