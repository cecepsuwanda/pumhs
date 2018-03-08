<?php
require_once 'default_table.class.inc';
class tb_krs extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->tablename       = 'tmst_krs';
        
		$this->fieldlist       = array('thsmskrs','fak','prodi','semkrs','shiftkrs','kelaskrs','nokmkkrs','noktphskrs','nlakhkrs','bobotkrs','kampus','mhsudate','optudate','optuid','nilaikrs');
        
		$this->sql_orderby     = "";
		
		$this->fieldlist['thsmskrs'] = array('pkey' => 'y');
		$this->fieldlist['fak'] = array('pkey' => 'y');
		$this->fieldlist['prodi'] = array('pkey' => 'y');
		$this->fieldlist['noktphskrs'] = array('pkey' => 'y');
		$this->fieldlist['nokmkkrs'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>
