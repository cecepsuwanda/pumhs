<?php
require_once 'default_table.class.inc';
class tb_opt_ctk_log extends Default_Table
{
    // additional class variables go here
    function __construct()
    {
        $this->tablename       = 'opt_ctk_log';
        $this->sql_orderby     = 'tgl_ctk desc';
		
        $this->fieldlist       = array('nm_file', 'tgl_ctk', 'userid');
        $this->fieldlist['nm_file'] = array('pkey' => 'y');
		      
				
    } // end class constructor

} // end class


?>