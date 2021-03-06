#ifndef ARDUINO_TEENSY_DMA_SPI_MASTER_TLC_H
#define ARDUINO_TEENSY_DMA_SPI_MASTER_TLC_H
#if defined (KINETISL)

#include "MasterBase.h"

inline void tsydmaspi_rxisr_0();
inline void tsydmaspi_rxisr_1();


ARDUINO_TEENSY_DMA_SPI_NAMESPACE_BEGIN


struct Master0 : public MasterBase
{
    friend void tsydmaspi_rxisr_0();

    virtual ~Master0()
    {
        destroy();
    }

    bool begin(const uint8_t cs, const bool active_low = true)
    {
        return this->MasterBase::begin(SPI, cs, SPISettings(), active_low);
    }

    bool begin(const uint8_t cs, const SPISettings& setting, const bool active_low = true)
    {
        return this->MasterBase::begin(SPI, cs, setting, active_low);
    }

    virtual DMAChannel* dmarx() override final
    {
        static DMAChannel *rx = new DMAChannel();
        return rx;
    }

    virtual DMAChannel* dmatx() override final
    {
        static DMAChannel *tx = new DMAChannel();
        return tx;
    }

    virtual bool initDmaTx() override final
    {
        if (dmatx() == nullptr)
        {
            Serial.println("[ERROR] create dma tx buffer failed");
            return false;
        }
        // TODO:
        // txChannel_()->disable();
        // txChannel_()->destination((volatile uint8_t&)SPI1_PUSHR);
        // txChannel_()->disableOnCompletion();
        // txChannel_()->triggerAtHardwareEvent(DMAMUX_SOURCE_SPI1_TX);
        if (dmatx()->error())
        {
            delete dmatx();
            return false;
        }
        return true;
    }

    virtual bool initDmaRx() override final
    {
        if (dmarx() == nullptr)
        {
            Serial.println("[ERROR] create dma tx buffer failed");
            return false;
        }
        // TODO:
        // rxChannel_()->disable();
        // rxChannel_()->source((volatile uint8_t&)SPI1_POPR);
        // rxChannel_()->disableOnCompletion();
        // rxChannel_()->triggerAtHardwareEvent(DMAMUX_SOURCE_SPI1_RX);
        // rxChannel_()->attachInterrupt(rxIsr_);
        // rxChannel_()->interruptAtCompletion();
        if (dmarx()->error())
        {
            delete dmarx();
            return false;
        }
        return true;
    }

    virtual void destroy() override final
    {
        if (dmarx() != nullptr) delete dmarx();
        if (dmatx() != nullptr) delete dmatx();
    }

    virtual void initTransaction() override final
    {
        // TODO:
        // SPI1_SR = 0xFF0F0000;
        // SPI1_RSER = SPI_RSER_RFDF_RE | SPI_RSER_RFDF_DIRS | SPI_RSER_TFFF_RE | SPI_RSER_TFFF_DIRS;
    }

    virtual void clearTransaction() override final
    {
        // TODO:
        // SPI1_RSER = 0;
        // SPI1_SR = 0xFF0F0000;
    }

};

struct Master1 : public MasterBase
{
    friend void tsydmaspi_rxisr_1();

    virtual ~Master1()
    {
        destroy();
    }

    bool begin(const uint8_t cs, const bool active_low = true)
    {
        return this->MasterBase::begin(SPI1, cs, SPISettings(), active_low);
    }

    bool begin(const uint8_t cs, const SPISettings& setting, const bool active_low = true)
    {
        return this->MasterBase::begin(SPI1, cs, setting, active_low);
    }

    virtual DMAChannel* dmarx() override final
    {
        static DMAChannel *rx = new DMAChannel();
        return rx;
    }

    virtual DMAChannel* dmatx() override final
    {
        static DMAChannel *tx = new DMAChannel();
        return tx;
    }

    virtual bool initDmaTx() override final
    {
        if (dmatx() == nullptr)
        {
            Serial.println("[ERROR] create dma tx buffer failed");
            return false;
        }
        // TODO:
        // dmatx()->disable();
        // dmatx()->destination((volatile uint8_t &)IMXRT_LPSPI3_S.TDR);
        // dmatx()->disableOnCompletion();
        // dmatx()->triggerAtHardwareEvent(DMAMUX_SOURCE_LPSPI3_TX);
        if (dmatx()->error())
        {
            delete dmatx();
            return false;
        }
        return true;
    }

    virtual bool initDmaRx() override final
    {
        if (dmarx() == nullptr)
        {
            Serial.println("[ERROR] create dma tx buffer failed");
            return false;
        }
        // TODO:
        // dmarx()->disable();
        // dmarx()->source((volatile uint8_t &)IMXRT_LPSPI3_S.RDR);
        // dmarx()->disableOnCompletion();
        // dmarx()->triggerAtHardwareEvent(DMAMUX_SOURCE_LPSPI3_RX);
        // dmarx()->attachInterrupt(tsydmaspi_rxisr_1);
        // dmarx()->interruptAtCompletion();
        if (dmarx()->error())
        {
            delete dmarx();
            return false;
        }
        return true;
    }

    virtual void destroy() override final
    {
        if (dmarx() != nullptr) delete dmarx();
        if (dmatx() != nullptr) delete dmatx();
    }

    virtual void initTransaction() override final
    {
        // TODO:
        // IMXRT_LPSPI3_S.TCR = (IMXRT_LPSPI3_S.TCR & ~(LPSPI_TCR_FRAMESZ(31))) | LPSPI_TCR_FRAMESZ(7);
        // IMXRT_LPSPI3_S.FCR = 0;
        // // Lets try to output the first byte to make sure that we are in 8 bit mode...
        // IMXRT_LPSPI3_S.DER = LPSPI_DER_TDDE | LPSPI_DER_RDDE; //enable DMA on both TX and RX
        // IMXRT_LPSPI3_S.SR = 0x3f00;                           // clear out all of the other status...
    }

    virtual void clearTransaction() override final
    {
        // TODO:
        // IMXRT_LPSPI3_S.FCR = LPSPI_FCR_TXWATER(15); // _spi_fcr_save; // restore the FSR status...
        // IMXRT_LPSPI3_S.DER = 0;                     // DMA no longer doing TX (or RX)
        // IMXRT_LPSPI3_S.CR = LPSPI_CR_MEN | LPSPI_CR_RRF | LPSPI_CR_RTF; // actually clear both...
        // IMXRT_LPSPI3_S.SR = 0x3f00;                                     // clear out all of the other status...
    }

};


ARDUINO_TEENSY_DMA_SPI_NAMESPACE_END


static TsyDMASPI::Master0 TsyDMASPI0;
static TsyDMASPI::Master1 TsyDMASPI1;

inline void tsydmaspi_rxisr_0()
{
    TsyDMASPI0.dmarx()->clearInterrupt();
    TsyDMASPI0.next();
}

inline void tsydmaspi_rxisr_1()
{
    TsyDMASPI1.dmarx()->clearInterrupt();
    TsyDMASPI1.next();
}

#endif // defined (KINETISL)
#endif // ARDUINO_TEENSY_DMA_SPI_MASTER_TLC_H
