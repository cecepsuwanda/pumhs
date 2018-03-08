<?php
require_once 'default_table.class.inc';
class tb_fak extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->tablename       = 'tmst_fakultas';
        
		$this->fieldlist       = array(`kd_fakultas`, `fakultas`);
        
		$this->sql_orderby         = 'kd_fakultas';
		
		$this->fieldlist['kd_fakultas'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>