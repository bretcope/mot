mod error;
pub use self::error::ParsingError;

mod tokens;
pub use self::tokens::{Token, TokenType};

mod lexer;
pub use self::lexer::*; // todo: don't really need to expose this long-term

pub mod nodes;

mod parser;
pub use self::parser::*;

#[derive(Debug)]
pub enum SyntaxElement<'a> {
    Token(&'a Token<'a>),
    Node(&'a nodes::Node<'a>),
}
