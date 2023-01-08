#pragma once

#include <gtest/gtest.h>

class BaseApplicationTest : public ::testing::Test
{
protected:
    static void SetUpTestCase();
    static void TearDownTestCase();
};
