<?php
declare(strict_types=1);

/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Test\Unit\Mvc\Application;

use UnitTester;

/**
 * Class UseImplicitViewCest
 */
class UseImplicitViewCest
{
    /**
     * Tests Phalcon\Mvc\Application :: useImplicitView()
     *
     * @param UnitTester $I
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function mvcApplicationUseImplicitView(UnitTester $I)
    {
        $I->wantToTest('Mvc\Application - useImplicitView()');
        $I->skipTest('Need implementation');
    }
}
