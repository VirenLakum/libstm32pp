/*******************************************************************************
 *
 * Copyright (C) 2012 Jorge Aparicio <jorge.aparicio.r@gmail.com>
 *
 * This file is part of libstm32pp.
 *
 * libstm32pp is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * libstm32pp is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libstm32pp. If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#pragma once

namespace flash {

#ifndef VALUE_LINE
  template<
      registers::acr::bits::latency::states::E LATENCY
  > void Functions::setLatency(void)
  {
    FLASH_REGS->ACR &= ~registers::acr::bits::latency::MASK;
    FLASH_REGS->ACR |= LATENCY;
  }
#endif
#ifdef STM32F1XX
#ifndef VALUE_LINE
  /**
   * @brief Enables the prefetch buffer.
   */
  void Functions::enablePrefetch(void)
  {
    FLASH_REGS->ACR |= registers::acr::bits::prftbe::states::PREFETCH_ENABLED;
  }

  /**
   * @brief Disables the prefetch buffer.
   */
  void Functions::disablePrefetch(void)
  {
    FLASH_REGS->ACR &= ~registers::acr::bits::prftbe::states::PREFETCH_ENABLED;
  }
#endif

  /**
   * @brief Enables the half cycle flash access.
   */
  void Functions::enableHalfCycleFlashAccess(void)
  {
    FLASH_REGS->ACR |=
    registers::acr::bits::hlfcya::states::FLASH_HALF_CYCLE_ACCESS_ENABLED;
  }

  /**
   * @brief Disables the half cycle flash access.
   */
  void Functions::disableHalfCycleFlashAccess(void)
  {
    FLASH_REGS->ACR &=
    ~registers::acr::bits::hlfcya::states::FLASH_HALF_CYCLE_ACCESS_ENABLED;
  }
#ifdef VALUE_LINE

  /**
   * @brief Configures the flash memory access.
   * @note  Overrides the old configuration.
   */
  template <
  registers::acr::bits::hlfcya::states::E HLFCYA
  >
  void Functions::configure(void)
  {
    FLASH_REGS->ACR = HLFCYA;
  }

#else // VALUE_LINE
  /**
   * @brief Configures the flash memory access.
   * @note  Overrides the old configuration.
   */
  template<
  registers::acr::bits::latency::states::E LATENCY,
  registers::acr::bits::hlfcya::states::E HLFCYA,
  registers::acr::bits::prftbe::states::E PRFTBE
  >
  void Functions::configure(void)
  {
    FLASH_REGS->ACR = LATENCY + HLFCYA + PRFTBE;
  }
#endif // VALUE_LINE
#else
  /**
   * @brief Enables the prefetch buffer.
   */
  void Functions::enablePrefetch(void)
  {
    FLASH_REGS->ACR |=
        registers::acr::bits::prften::states::PREFETCH_ENABLED;
  }

  /**
   * @brief Disables the prefetch buffer.
   */
  void Functions::disablePrefetch(void)
  {
    FLASH_REGS->ACR &=
        ~registers::acr::bits::prften::states::PREFETCH_ENABLED;
  }

  /**
   * @brief Enables the data cache.
   */
  void Functions::enableDataCache(void)
  {
    FLASH_REGS->ACR |=
        registers::acr::bits::dcen::states::DATA_CACHE_ENABLED;
  }

  /**
   * @brief Disables the data cache.
   */
  void Functions::disableDataCache(void)
  {
    FLASH_REGS->ACR &=
        ~registers::acr::bits::dcen::states::DATA_CACHE_ENABLED;
  }

  /**
   * @brief Enables the instruction cache.
   */
  void Functions::enableInstructionCache(void)
  {
    FLASH_REGS->ACR |=
        registers::acr::bits::icen::states::INSTRUCTION_CACHE_ENABLED;
  }

  /**
   * @brief Disables the instruction cache.
   */
  void Functions::disableInstructionCache(void)
  {
    FLASH_REGS->ACR &=
        ~registers::acr::bits::icen::states::INSTRUCTION_CACHE_ENABLED;
  }

  /**
   * @brief Configures the flash memory access.
   * @note  Overrides the old configuration.
   */
  template<
      registers::acr::bits::latency::states::E LATENCY,
      registers::acr::bits::prften::states::E PRFTEN,
      registers::acr::bits::dcen::states::E DCEN,
      registers::acr::bits::icen::states::E ICEN
  >
  void Functions::configure(void)
  {
    FLASH_REGS->ACR = LATENCY + PRFTEN + DCEN + ICEN;
  }
#endif

}  // namespace flash
