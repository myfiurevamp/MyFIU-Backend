# Myfiurevamp-backend
Backend for MyFIU

## Postgres Database:

<strong>IMPORTANT</strong>: Read all comments in all SQL files! Important rules regarding tables, queries, and functions are documented that 
must be adhered to!

### Main functions include:
  - inserting/updating students
  - validating superusers and guests
  - inserting offered courses
  - recording transcripts
  
### To connect to the database:
  - install <a href="http://www.enterprisedb.com/products-services-training/pgdownload">PostgreSQL</a>
  - open up a terminal window and type <code>psql -h hostname -U postgres</code> where <code>hostname</code> is the name of the host or the IP address that the database is on.
  - enter password
  - connect to database enter <code>\c myfiurevamp</code>
  
### When connected to the database:  
All SQL queries can be performed on the command line. Try <code>select * from student;</code>
</br>
</br>
<strong>Note</strong>: When executing queries, be sure to end them with a semicolon <code>;</code> or psql will think you are entering a new line. If this happens, simply type <code>;</code> and enter a new line.

To list all tables, enter <code>\dt</code>. To describe a table, enter <code>\d table-name</code>.




