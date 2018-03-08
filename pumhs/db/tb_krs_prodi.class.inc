<?php
require_once 'default_table.class.inc';
class tb_krs_prodi extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->tablename       = 'krs_prodi';
        
		$this->fieldlist       = array('thsmskrs','kd_fakultas','kd_prodi','prodi');
        
		$this->sql_orderby     = "";
		
		$this->fieldlist['thsmskrs'] = array('pkey' => 'y');
		$this->fieldlist['kd_fakultas'] = array('pkey' => 'y');
		$this->fieldlist['kd_prodi'] = array('pkey' => 'y');
		$this->fieldlist['prodi'] = array('pkey' => 'y');
		
		        
				
    } // end class constructor

} // end class
?>
