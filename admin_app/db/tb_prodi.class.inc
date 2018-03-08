<?php
require_once 'default_table.class.inc';
class tb_prodi extends Default_Table
{
    // additional class variables go here
    function tb_prodi ()
    {
        $this->tablename       = 'tmst_prodi';
        
		$this->fieldlist       = array('kd_prodi',`kd_fakultas`, `prodi`,'sn_prodi');
        
		$this->sql_orderby         = 'kd_fakultas,kd_prodi';
		
		$this->fieldlist['kd_prodi'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>