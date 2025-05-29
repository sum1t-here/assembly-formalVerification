//1.  0x6080604052 348015600e575f5ffd5b506101298061001c5f395ff3

//2. fe6080604052348015600e575f5ffd5b50600436106030575f3560e01c
//   806367d41eca146034578063e026c01714604c575b5f5ffd5b604a6004
//   8036038101906046919060a9565b6066565b005b6052606f565b604051
//   605d919060 dc565b60405180910390f35b805f8190555050565b5f5f54905090565b5f5ffd5b5f8190509190505
// 65b608b81607b565b81146094575f5ffd5b50565b5f8135905060a3816084565b92915050565b5f60
// 20828403121560bb5760ba6077565b5b5f60c6848285016097565b91505092915050565b60d681607b
// 565b82525050565b5f60208201905060ed5f83018460cf565b9291505056

//3. fea2646970667358221220ab4fb2620b8cbd118c3edf223dec46659496a851b292af84ecf9fd
//   a6d819f7a764736f6c634300081c0033

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
SUB                 // [calldatasize - 0x04 (arg_length), 0x04, 0x4a, func_selector]
DUP2                // [0x04, arg_length, 0x04, 0x4a, func_selector]
ADD                 // [0x04 + arg_length, 0x04, 0x4a, func_selector]
SWAP1               // [0x04, offset + arg_length, 0x4a, func_selector]
PUSH1 0x46          // [0x46, 0x04, offset + arg_length, 0x4a, func_selector]
SWAP2               // offset + arg_length, 0x04, 0x46, 0x4a, func_selector]
SWAP1               // [0x04, coffset + arg_length, 0x46, 0x4a, func_selector]
PUSH1 0xa9          // [0xa9, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
JUMP                // jump to 0xa9

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

// 0x7b
JUMPDEST                 // [arg_data, 0x8b, arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
PUSH0                    // [0, arg_data, 0x8b, arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
DUP2                     // [arg_data, 0, arg_data, 0x8b, arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
SWAP1                    // [0,arg_data,  arg_data, 0x8b, arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
POP                      // [arg_data,  arg_data, 0x8b, arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
SWAP2                    // [0x8b, arg_data,  arg_data,  arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
SWAP1                    // [arg_data, 0x8b, arg_data,  arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
POP                      // [0x8b, arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
JUMP                     // jump to 0x8b

// 0x84
JUMPDEST                        // [arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
PUSH1 0x8b                      // [0x8b, arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
DUP2                            // [arg_data, 0x8b, arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
PUSH1 0x7b                      // [0x7b, arg_data, 0x8b, arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
JUMP                            // jump to 0x7b

// 0x8b
JUMPDEST                        // [arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
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

// 0x97
JUMPDEST                                // [0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
PUSH0                                   // [0, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
DUP2                                    // [0x04, 0, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
CALLDATALOAD                            // [arg_data, 0, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
SWAP1                                   // [0, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
POP                                     // [arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
PUSH1 0xa3                              // [0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
DUP2                                    // [arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
PUSH1 0x84                              // [0x84, arg_data, 0xa3, arg_data, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
JUMP                                    // jump to 0x84

JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP

// 0xa9
JUMPDEST                            // [0x04, offset + arg_length, 0x46, 0x4a, func_selector]
// 0x04 = calldata offset (usually 4 bytes, after function selector)
// offset + arg_length = end of calldata slice (offset + length of args)
// 0x46 = destination memory offset for calldatacopy
// 0x4a = some memory related offset (possibly size or scratch space)
// func_selector = original function selector from calldata
PUSH0                               // [0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
PUSH1 0x20                          // [0x20 ,0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
DUP3                                // [0x04 ,0x20 ,0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
DUP5                                // [offset + arg_length, 0x04 ,0x20 ,0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
SUB                                 // [arg_length, 0x20 ,0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
SLT                                 // [arg_length < 0x20 ,0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
ISZERO                              // [(arg_length < 0x20 == 0) , 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
PUSH1 0xbb                          // [0xbb ,(arg_length < 0x20 == 0) , 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
JUMPI                               // conditional jump to 0xbb

PUSH1 0xba                          // [0xba ,0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
PUSH1 0x77                          // [0x77, 0xba ,0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
JUMP                                // jump to 0x77

JUMPDEST
// 0xbb
JUMPDEST                            // [0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
PUSH0                               // [0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
PUSH1 0xc6                          // [0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
DUP5                                // [offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
DUP3                                // [0, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
DUP6                                // [0x04, 0, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
ADD                                 // [0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
PUSH1 0x97                          // [0x97, 0x04, offset + arg_length, 0xc6, 0, 0, 0x04, offset + arg_length, 0x46, 0x4a, func_selector]
JUMP                                // jump to 0x97

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

// 3. Metadata
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