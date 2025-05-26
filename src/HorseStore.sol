// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.26;

contract HorseStore {
    uint256 numberOfHorses;

    function updateNumberOfHorses(uint256 newNumberOfHorses) external {
        numberOfHorses = newNumberOfHorses;
    }

    function readNumberOfHorses() external view returns (uint256) {
        return numberOfHorses;
    }
}
