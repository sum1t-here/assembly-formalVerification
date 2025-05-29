// SPDX-License-Identifier: MIT
pragma solidity ^0.8.26;

contract HorseStoreYul {
    uint256 numberOfHorses; // 0

    function updateNumberOfHorses(uint256 newNumberOfHorses) external {
        assembly {
            // YUL GOES HERE
            sstore(numberOfHorses.slot, newNumberOfHorses)
        }
    }

    function readNumberOfHorses() external view returns (uint256) {
        assembly {
            // YUL GOES HERE
            let num := sload(numberOfHorses.slot)
            mstore(0, num)
            return(0, 0x20)
        }
    }
}