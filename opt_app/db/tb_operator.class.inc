<?php
require_once 'default_table.class.inc';
class tb_operator extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->tablename       = 'tmst_operator';
        
		$this->fieldlist       = array('id_opt','nama_user','user','pass');
        
		$this->sql_orderby         = 'id_opt';
		
		$this->fieldlist['id_opt'] = array('pkey' => 'y');
		
		        
				
    } // end class constructor

} // end class
?>